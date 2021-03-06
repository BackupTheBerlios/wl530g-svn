/*
 * Host AP (software wireless LAN access point) user space daemon for
 * Host AP kernel driver / Station table
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. See README and COPYING for
 * more details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "hostapd.h"
#include "sta_info.h"
#include "eloop.h"
#include "accounting.h"
#include "ieee802_1x.h"
#include "ieee802_11.h"
#include "radius.h"
#include "driver.h"


struct sta_info* ap_get_sta(hostapd *hapd, u8 *sta)
{
	struct sta_info *s;

	s = hapd->sta_hash[STA_HASH(sta)];
	while (s != NULL && memcmp(s->addr, sta, 6) != 0)
		s = s->hnext;
	return s;
}


struct sta_info* ap_get_sta_radius_identifier(hostapd *hapd,
					      u8 radius_identifier)
{
	struct sta_info *s;

	s = hapd->sta_list;

	while (s) {
		if (s->radius_identifier >= 0 &&
		    s->radius_identifier == radius_identifier)
			return s;
		s = s->next;
	}

	return NULL;
}


static void ap_sta_list_del(hostapd *hapd, struct sta_info *sta)
{
	struct sta_info *tmp;

	if (hapd->sta_list == sta) {
		hapd->sta_list = sta->next;
		return;
	}

	tmp = hapd->sta_list;
	while (tmp != NULL && tmp->next != sta)
		tmp = tmp->next;
	if (tmp == NULL) {
		printf("Could not remove STA " MACSTR " from list.\n",
		       MAC2STR(sta->addr));
	} else
		tmp->next = sta->next;
}


void ap_sta_hash_add(hostapd *hapd, struct sta_info *sta)
{
	sta->hnext = hapd->sta_hash[STA_HASH(sta->addr)];
	hapd->sta_hash[STA_HASH(sta->addr)] = sta;
}


static void ap_sta_hash_del(hostapd *hapd, struct sta_info *sta)
{
	struct sta_info *s;

	s = hapd->sta_hash[STA_HASH(sta->addr)];
	if (s == NULL) return;
	if (memcmp(s->addr, sta->addr, 6) == 0) {
		hapd->sta_hash[STA_HASH(sta->addr)] = s->hnext;
		return;
	}

	while (s->hnext != NULL && memcmp(s->hnext->addr, sta->addr, 6) != 0)
		s = s->hnext;
	if (s->hnext != NULL)
		s->hnext = s->hnext->hnext;
	else
		printf("AP: could not remove STA " MACSTR " from hash table\n",
		       MAC2STR(sta->addr));
}


void ap_free_sta(hostapd *hapd, struct sta_info *sta)
{
	struct prism2_hostapd_param param;

	accounting_sta_stop(hapd, sta);

	memset(&param, 0, sizeof(param));
	param.cmd = PRISM2_HOSTAPD_REMOVE_STA;
	memcpy(param.sta_addr, sta->addr, ETH_ALEN);
	if (hostapd_ioctl(hapd, &param, sizeof(param))) {
		printf("Could not remove station from kernel driver.\n");
	}

	ap_sta_hash_del(hapd, sta);
	ap_sta_list_del(hapd, sta);

	if (sta->aid > 0)
		hapd->sta_aid[sta->aid - 1] = NULL;

	hapd->num_sta--;
	eloop_cancel_timeout(ap_handle_timer, hapd, sta);

	ieee802_1x_free_station(sta);

	if (sta->last_assoc_req)
		free(sta->last_assoc_req);

	free(sta->challenge);

	free(sta);
}


void hostapd_free_stas(hostapd *hapd)
{
	struct sta_info *sta, *prev;

	sta = hapd->sta_list;

	while (sta) {
		prev = sta;
		sta = sta->next;
		printf("Removing station " MACSTR "\n", MAC2STR(prev->addr));
		ap_free_sta(hapd, prev);
	}
}


void ap_handle_timer(void *eloop_ctx, void *timeout_ctx)
{
	hostapd *hapd = eloop_ctx;
	struct sta_info *sta = timeout_ctx;
	unsigned long next_time = 0;
	struct prism2_hostapd_param param;

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "Checking STA " MACSTR " inactivity:\n",
		      MAC2STR(sta->addr));
	memset(&param, 0, sizeof(param));
	param.cmd = PRISM2_HOSTAPD_GET_INFO_STA;
	memcpy(param.sta_addr, sta->addr, ETH_ALEN);
	if (hostapd_ioctl(hapd, &param, sizeof(param))) {
		printf("  Could not get station info from kernel driver.\n");
		/* assume the station has expired */
		param.u.get_info_sta.inactive_sec = AP_MAX_INACTIVITY + 1;
		param.u.get_info_sta.txexc = 1;
	}

	if (param.u.get_info_sta.inactive_sec < AP_MAX_INACTIVITY) {
		/* station activity detected; reset timeout state */
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
			      "  Station has been active\n");
		sta->timeout_next = STA_NULLFUNC;
		next_time = AP_MAX_INACTIVITY -
			param.u.get_info_sta.inactive_sec;
	} else if (sta->timeout_next == STA_DISASSOC &&
		   param.u.get_info_sta.txexc == 0) {
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
			      "  Station has ACKed data poll\n");
		/* data nullfunc frame poll did not produce TX errors; assume
		 * station ACKed it */
		sta->timeout_next = STA_NULLFUNC;
		next_time = AP_MAX_INACTIVITY;
	}

	if (next_time) {
		eloop_register_timeout(next_time, 0, ap_handle_timer, hapd,
				       sta);
		return;
	}

	if (sta->timeout_next == STA_NULLFUNC) {
		/* send data frame to poll STA and check whether this frame
		 * is ACKed */
		struct ieee80211_hdr hdr;

		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
			      "  Polling STA with data frame\n");
		memset(&param, 0, sizeof(param));
		param.cmd = PRISM2_HOSTAPD_RESET_TXEXC_STA;
		memcpy(param.sta_addr, sta->addr, ETH_ALEN);
		if (hostapd_ioctl(hapd, &param, sizeof(param))) {
			printf("  Could not reset station TX Exc counter\n");
		}

		/* FIX: WLAN_FC_STYPE_NULLFUNC would be more appropriate, but
		 * it is apparently not retried so TX Exc events are not
		 * received for it */
		memset(&hdr, 0, sizeof(hdr));
		hdr.frame_control =
			IEEE80211_FC(WLAN_FC_TYPE_DATA, WLAN_FC_STYPE_DATA);
		hdr.frame_control |= host_to_le16(BIT(1));
		hdr.frame_control |= host_to_le16(WLAN_FC_FROMDS);
		memcpy(hdr.IEEE80211_DA_FROMDS, sta->addr, ETH_ALEN);
		memcpy(hdr.IEEE80211_BSSID_FROMDS, hapd->own_addr, ETH_ALEN);
		memcpy(hdr.IEEE80211_SA_FROMDS, hapd->own_addr, ETH_ALEN);

		if (send(hapd->sock, &hdr, sizeof(hdr), 0) < 0)
			perror("ap_handle_timer: send");
	} else {
		int deauth = sta->timeout_next == STA_DEAUTH;

		printf("  Sending %s info to STA " MACSTR "\n",
		       deauth ? "deauthentication" : "disassociation",
		       MAC2STR(sta->addr));

		if (deauth) {
			ieee802_11_send_deauth(
				hapd, sta->addr,
				WLAN_REASON_PREV_AUTH_NOT_VALID);
		} else {
			ieee802_11_send_disassoc(
				hapd, sta->addr,
				WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY);
		}
	}

	switch (sta->timeout_next) {
	case STA_NULLFUNC:
		sta->timeout_next = STA_DISASSOC;
		eloop_register_timeout(AP_DISASSOC_DELAY, 0, ap_handle_timer,
				       hapd, sta);
		break;
	case STA_DISASSOC:
		sta->flags &= ~WLAN_STA_ASSOC;
		ieee802_1x_set_port_enabled(hapd, sta, 0);
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_INFO, "disassociated due to "
			       "inactivity");
		sta->timeout_next = STA_DEAUTH;
		eloop_register_timeout(AP_DEAUTH_DELAY, 0, ap_handle_timer,
				       hapd, sta);
		break;
	case STA_DEAUTH:
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_INFO, "deauthenticated due to "
			       "inactivity");
		if (!sta->acct_terminate_cause)
			sta->acct_terminate_cause =
				RADIUS_ACCT_TERMINATE_CAUSE_IDLE_TIMEOUT;
		ap_free_sta(hapd, sta);
		break;
	}
}


void ap_handle_session_timer(void *eloop_ctx, void *timeout_ctx)
{
	hostapd *hapd = eloop_ctx;
	struct sta_info *sta = timeout_ctx;

	if (!(sta->flags & WLAN_STA_AUTH))
		return;

	ieee802_11_send_deauth(hapd, sta->addr,
			       WLAN_REASON_PREV_AUTH_NOT_VALID);
	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_INFO, "deauthenticated due to "
		       "session timeout");
	sta->acct_terminate_cause =
		RADIUS_ACCT_TERMINATE_CAUSE_SESSION_TIMEOUT;
	ap_free_sta(hapd, sta);
}


void ap_sta_session_timeout(hostapd *hapd, struct sta_info *sta,
			    u32 session_timeout)
{
	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_DEBUG, "setting session timeout to %d "
		       "seconds", session_timeout);
	eloop_cancel_timeout(ap_handle_session_timer, hapd, sta);
	eloop_register_timeout(session_timeout, 0, ap_handle_session_timer,
			       hapd, sta);
}


void ap_sta_no_session_timeout(hostapd *hapd, struct sta_info *sta)
{
	eloop_cancel_timeout(ap_handle_session_timer, hapd, sta);
}
