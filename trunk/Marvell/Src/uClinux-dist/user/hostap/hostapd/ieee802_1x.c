/*
 * Host AP (software wireless LAN access point) user space daemon for
 * Host AP kernel driver / IEEE 802.1X Authenticator
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. See README and COPYING for
 * more details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>


#include "hostapd.h"
#include "ieee802_1x.h"
#include "accounting.h"
#include "radius.h"
#include "radius_client.h"
#include "eapol_sm.h"
#include "md5.h"
#include "rc4.h"
#include "eloop.h"
#include "sta_info.h"
#include "driver.h"


static void ieee802_1x_send(hostapd *hapd, struct sta_info *sta, u8 type,
			    u8 *data, size_t datalen)
{
	char *buf;
	struct ieee80211_hdr *hdr;
	struct ieee802_1x_hdr *xhdr;
	size_t len;
	u8 *pos;

	len = sizeof(*hdr) + sizeof(rfc1042_header) + 2 + sizeof(*xhdr) +
		datalen;
	buf = (char *) malloc(len);
	if (buf == NULL) {
		printf("malloc() failed for ieee802_1x_send(len=%d)\n", len);
		return;
	}

	memset(buf, 0, len);

	hdr = (struct ieee80211_hdr *) buf;
	hdr->frame_control =
		IEEE80211_FC(WLAN_FC_TYPE_DATA, WLAN_FC_STYPE_DATA);
	hdr->frame_control |= host_to_le16(WLAN_FC_FROMDS);
	/* Request TX callback */
	hdr->frame_control |= host_to_le16(BIT(1));
#if 0
	/* TODO:
	 * According to IEEE 802.1aa/D4 EAPOL-Key should be sent before any
	 * remaining EAP frames, if possible. This would allow rest of the
	 * frames to be encrypted. This code could be used to request
	 * encryption from the kernel driver. */
	if (sta->eapol_sm &&
	    sta->eapol_sm->be_auth.state == BE_AUTH_SUCCESS &&
	    sta->eapol_sm->keyTxEnabled)
		hdr->frame_control |= host_to_le16(WLAN_FC_ISWEP);
#endif
	memcpy(hdr->IEEE80211_DA_FROMDS, sta->addr, ETH_ALEN);
	memcpy(hdr->IEEE80211_BSSID_FROMDS, hapd->own_addr, ETH_ALEN);
	memcpy(hdr->IEEE80211_SA_FROMDS, hapd->own_addr, ETH_ALEN);

	pos = (u8 *) (hdr + 1);
	memcpy(pos, rfc1042_header, sizeof(rfc1042_header));
	pos += sizeof(rfc1042_header);

	*((u16 *) pos) = htons(ETH_P_PAE);
	pos += 2;

	xhdr = (struct ieee802_1x_hdr *) pos;
	xhdr->version = EAPOL_VERSION;
	xhdr->type = type;
	xhdr->length = htons(datalen);

	if (datalen > 0 && data != NULL)
		memcpy(xhdr + 1, data, datalen);

	if (send(hapd->sock, buf, len, 0) < 0) {
		perror("ieee802_1x_send: send");
		printf("ieee802_1x_send - packet len: %d - failed\n", len);
	}

	free(buf);
}


void ieee802_1x_set_sta_authorized(hostapd *hapd, struct sta_info *sta,
				   int authorized)
{
	struct prism2_hostapd_param param;

	memset(&param, 0, sizeof(param));
	param.cmd = PRISM2_HOSTAPD_SET_FLAGS_STA;
	memcpy(param.sta_addr, sta->addr, ETH_ALEN);
	if (authorized) {
		sta->flags |= WLAN_STA_AUTHORIZED;
		param.u.set_flags_sta.flags_or = WLAN_STA_AUTHORIZED;
		param.u.set_flags_sta.flags_and = ~0;
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG, "authorizing port");
		accounting_sta_start(hapd, sta);
	} else {
		sta->flags &= ~WLAN_STA_AUTHORIZED;
		param.u.set_flags_sta.flags_and = ~WLAN_STA_AUTHORIZED;
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG, "unauthorizing port");
	}

	if (hostapd_ioctl(hapd, &param, sizeof(param)))
		printf("Could not set station flags for kernel driver.\n");
}


void ieee802_1x_request_identity(hostapd *hapd, struct sta_info *sta, u8 id)
{
	char *buf;
	struct eap_hdr *eap;
	int extra, tlen;
	u8 *pos;

	ieee802_1x_new_auth_session(hapd, sta);

	if (hapd->conf->eap_req_id_text)
		extra = strlen(hapd->conf->eap_req_id_text);
	else
		extra = 0;

	tlen = sizeof(*eap) + 1 + extra;

	buf = (char *) malloc(tlen);
	if (buf == NULL) {
		printf("Could not allocate memory for identity request\n");
		return;
	}

	memset(buf, 0, tlen);

	eap = (struct eap_hdr *) buf;
	eap->code = EAP_CODE_REQUEST;
	eap->identifier = id;
	eap->length = htons(tlen);
	pos = (u8 *) (eap + 1);
	*pos++ = EAP_TYPE_IDENTITY;
	if (hapd->conf->eap_req_id_text)
		memcpy(pos, hapd->conf->eap_req_id_text, extra);

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: Sending EAP Request-Identity to " MACSTR
		      " (identifier %d)\n", MAC2STR(sta->addr),
		      eap->identifier);
	ieee802_1x_send(hapd, sta, IEEE802_1X_TYPE_EAP_PACKET, buf, tlen);
	free(buf);
}


void ieee802_1x_tx_canned_eap(hostapd *hapd, struct sta_info *sta, u8 id,
			      int success)
{
	struct eap_hdr eap;

	memset(&eap, 0, sizeof(eap));

	eap.code = success ? EAP_CODE_SUCCESS : EAP_CODE_FAILURE;
	eap.identifier = id;
	eap.length = htons(sizeof(eap));

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: Sending canned EAP packet %s to " MACSTR
		      " (identifier %d)\n", success ? "SUCCESS" : "FAILURE",
		      MAC2STR(sta->addr), eap.identifier);
	ieee802_1x_send(hapd, sta, IEEE802_1X_TYPE_EAP_PACKET, (u8 *) &eap,
			sizeof(eap));
}


void ieee802_1x_tx_req(hostapd *hapd, struct sta_info *sta, u8 id)
{
	struct eap_hdr *eap;

	if (sta->last_eap_radius == NULL) {
		printf("Error: TxReq called for station " MACSTR ", but there "
		       "is no EAP request from the authentication server\n",
		       MAC2STR(sta->addr));
		return;
	}

	eap = (struct eap_hdr *) sta->last_eap_radius;
	if (eap->identifier != id) {
		printf("IEEE 802.1X: TxReq(%d) - changing id from %d\n",
		       id, eap->identifier);
		eap->identifier = id;
	}

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: Sending EAP Packet to " MACSTR
		      " (identifier %d)\n", MAC2STR(sta->addr), id);
	ieee802_1x_send(hapd, sta, IEEE802_1X_TYPE_EAP_PACKET,
			sta->last_eap_radius, sta->last_eap_radius_len);
}


static void ieee802_1x_tx_key_one(hostapd *hapd, struct sta_info *sta,
				  int index, int broadcast,
				  u8 *key_data, size_t key_len)
{
	u8 *buf, *ekey;
	struct ieee802_1x_hdr *hdr;
	struct ieee802_1x_eapol_key *key;
	struct timeval now;
	size_t len, ekey_len;
	u32 ntp_hi, ntp_lo, sec, usec;

	len = sizeof(*key) + key_len;
	buf = malloc(sizeof(*hdr) + len);
	if (buf == NULL)
		return;

	memset(buf, 0, sizeof(*hdr) + len);
	hdr = (struct ieee802_1x_hdr *) buf;
	key = (struct ieee802_1x_eapol_key *) (hdr + 1);
	key->type = EAPOL_KEY_TYPE_RC4;
	key->key_length = htons(key_len);

	/* Set the NTP timestamp as the replay counter */
	gettimeofday(&now, NULL);
	sec = now.tv_sec;
	usec = now.tv_usec;

#define JAN_1970 0x83aa7e80UL /* seconds from 1900 to 1970 */
	ntp_hi = htonl(sec + JAN_1970);
	/* approximation of 2^32/1000000 * usec */
	ntp_lo = htonl(4295 * usec - (usec >> 5) - (usec >> 9));

	memcpy(&key->replay_counter[0], &ntp_hi, sizeof(u32));
	memcpy(&key->replay_counter[4], &ntp_lo, sizeof(u32));

	if (hostapd_get_rand(key->key_iv, sizeof(key->key_iv))) {
		printf("Could not get random numbers\n");
		free(buf);
		return;
	}

	key->key_index = index | (broadcast ? 0 : BIT(7));
	if (hapd->conf->eapol_key_index_workaround) {
		/* According to some information, WinXP Supplicant seems to
		 * interrept bit7 as an indication whether the key is to be
		 * activated, so make it possible to enable workaround that
		 * sets this bit for all keys. */
		key->key_index |= BIT(7);
	}

	/* Key is encrypted using "Key-IV + sta->eapol_key_crypt" as the
	 * RC4-key */
	memcpy((u8 *) (key + 1), key_data, key_len);
	ekey_len = sizeof(key->key_iv) + sta->eapol_key_crypt_len;
	ekey = malloc(ekey_len);
	if (ekey == NULL) {
		printf("Could not encrypt key\n");
		free(buf);
		return;
	}
	memcpy(ekey, key->key_iv, sizeof(key->key_iv));
	memcpy(ekey + sizeof(key->key_iv), sta->eapol_key_crypt,
	       sta->eapol_key_crypt_len);
	rc4((u8 *) (key + 1), key_len, ekey, ekey_len);
	free(ekey);

	/* This header is needed here for HMAC-MD5, but it will be regenerated
	 * in ieee802_1x_send() */
	hdr->version = EAPOL_VERSION;
	hdr->type = IEEE802_1X_TYPE_EAPOL_KEY;
	hdr->length = htons(len);
	hmac_md5(sta->eapol_key_sign, sta->eapol_key_sign_len,
		 buf, sizeof(*hdr) + len,
		 key->key_signature);

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: Sending EAPOL-Key to " MACSTR
		      " (%s index=%d)\n", MAC2STR(sta->addr),
		      broadcast ? "broadcast" : "unicast", index);
	ieee802_1x_send(hapd, sta, IEEE802_1X_TYPE_EAPOL_KEY, (u8 *) key, len);
	free(buf);
}


void ieee802_1x_tx_key(hostapd *hapd, struct sta_info *sta, u8 id)
{
	if (!sta->eapol_key_sign || !sta->eapol_key_crypt)
		return;

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: Sending EAPOL-Key(s) to " MACSTR
		      " (identifier %d)\n", MAC2STR(sta->addr), id);

	if (hapd->default_wep_key)
		ieee802_1x_tx_key_one(hapd, sta, hapd->default_wep_key_idx, 1,
				      hapd->default_wep_key,
				      hapd->conf->default_wep_key_len);

	if (hapd->conf->individual_wep_key_len > 0) {
		u8 *ikey;
		ikey = malloc(hapd->conf->individual_wep_key_len);
		if (ikey == NULL ||
		    hostapd_get_rand(ikey,
				     hapd->conf->individual_wep_key_len)) {
			printf("Could not generate random individual WEP "
			       "key.\n");
			free(ikey);
			return;
		}

		if (HOSTAPD_DEBUG_COND(HOSTAPD_DEBUG_MINIMAL))
			hostapd_hexdump("Individual WEP key",
					ikey,
					hapd->conf->individual_wep_key_len);

		ieee802_1x_tx_key_one(hapd, sta, 0, 0, ikey,
				      hapd->conf->individual_wep_key_len);

		/* TODO: set encryption in TX callback, i.e., only after STA
		 * has ACKed EAPOL-Key frame */
		if (hostapd_set_encryption(hapd, "WEP", sta->addr, 0, ikey,
					   hapd->conf->
					   individual_wep_key_len)) {
			printf("Could not set individual WEP encryption.\n");
		}

		free(ikey);
	}
}


/* This is just a minimal authentication server for testing the authenticator.
 * It accepts anything, i.e., no keys are needed and this should not be used
 * for anything else than testing.
 * Real implementation would forward the packet to an external authentication
 * server in ieee802_1x_send_resp_to_server() */

static void minimal_auth_serv_reply(u8 id, struct sta_info *sta, u8 eap_code)
{
	struct eap_hdr *eap;

	sta->eapol_sm->be_auth.idFromServer = id;

	if (sta->last_eap_radius)
		free(sta->last_eap_radius);

	sta->last_eap_radius = malloc(sizeof(*eap));
	if (sta->last_eap_radius == NULL) {
		printf("minimal_auth_serv_reply: could not add EAP data\n");
		return;
	}
	sta->last_eap_radius_len = sizeof(*eap);

	eap = (struct eap_hdr *) sta->last_eap_radius;
	memset(eap, 0, sizeof(*eap));
	eap->code = eap_code;
	eap->identifier = id;
	eap->length = sizeof(*eap);
}


static void minimal_auth_serv(hostapd *hapd, struct sta_info *sta,
			      u8 *data, size_t len)
{
	struct eap_hdr *eap;
	u8 *pos;
	size_t left;
	int i;
	static u8 id = 0;

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "Minimal Authentication Server\n");

	if (len < sizeof(*eap)) {
		printf("Too short packet for minimal auth serv\n");
		goto fail;
	}

	eap = (struct eap_hdr *) data;
	if (eap->code != EAP_CODE_RESPONSE) {
		printf("Invalid EAP code (%d) in minimal auth serv\n",
		       eap->code);
		goto fail;
	}

	pos = (u8 *) (eap + 1);
	left = len - sizeof(*eap);
	if (*pos != EAP_TYPE_IDENTITY) {
		printf("Invalid EAP Response type (%d) in minimal auth serv\n",
		       *pos);
		goto fail;
	}

	pos++;
	left--;

	printf("Minimal Authentication Server: station " MACSTR
	       " EAP Response-Identity: (len=%d) '", MAC2STR(sta->addr), len);
	for (i = 0; i < left; i++)
		print_char(pos[i]);
	printf("'\n");

	minimal_auth_serv_reply(id++, sta, EAP_CODE_SUCCESS);
	sta->eapol_sm->be_auth.aSuccess = TRUE;
	eapol_sm_step(sta->eapol_sm);
	return;

 fail:
	minimal_auth_serv_reply(id++, sta, EAP_CODE_FAILURE);
	sta->eapol_sm->be_auth.aFail = TRUE;
	eapol_sm_step(sta->eapol_sm);
}


static void ieee802_1x_encapsulate_radius(hostapd *hapd, struct sta_info *sta,
					  u8 *eap, size_t len)
{
	struct radius_msg *msg;
	char buf[128];

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "Encapsulating EAP message into a RADIUS packet\n");

	sta->radius_identifier = radius_client_get_id(hapd);
	msg = radius_msg_new(RADIUS_CODE_ACCESS_REQUEST,
			     sta->radius_identifier);
	if (msg == NULL) {
		printf("Could not create net RADIUS packet\n");
		return;
	}

	radius_msg_make_authenticator(msg, (u8 *) sta, sizeof(sta));

	if (sta->identity &&
	    !radius_msg_add_attr(msg, RADIUS_ATTR_USER_NAME,
				 sta->identity, sta->identity_len)) {
		printf("Could not add User-Name\n");
		goto fail;
	}

	if (!radius_msg_add_attr(msg, RADIUS_ATTR_NAS_IP_ADDRESS,
				 (u8 *) &hapd->conf->own_ip_addr, 4)) {
		printf("Could not add NAS-IP-Address\n");
		goto fail;
	}

	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_NAS_PORT, sta->aid)) {
		printf("Could not add NAS-Port\n");
		goto fail;
	}

	snprintf(buf, sizeof(buf), RADIUS_802_1X_ADDR_FORMAT ":%s",
		 MAC2STR(hapd->own_addr), hapd->conf->ssid);
	if (!radius_msg_add_attr(msg, RADIUS_ATTR_CALLED_STATION_ID,
				 buf, strlen(buf))) {
		printf("Could not add Called-Station-Id\n");
		goto fail;
	}

	snprintf(buf, sizeof(buf), RADIUS_802_1X_ADDR_FORMAT,
		 MAC2STR(sta->addr));
	if (!radius_msg_add_attr(msg, RADIUS_ATTR_CALLING_STATION_ID,
				 buf, strlen(buf))) {
		printf("Could not add Calling-Station-Id\n");
		goto fail;
	}

	/* TODO: should probably check MTU from driver config; 2304 is max for
	 * IEEE 802.11, but use 1400 to avoid problems with too large packets
	 */
	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_FRAMED_MTU, 1400)) {
		printf("Could not add Framed-MTU\n");
		goto fail;
	}

	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_NAS_PORT_TYPE,
				       RADIUS_NAS_PORT_TYPE_IEEE_802_11)) {
		printf("Could not add NAS-Port-Type\n");
		goto fail;
	}

	snprintf(buf, sizeof(buf), "CONNECT 11Mbps 802.11b");
	if (!radius_msg_add_attr(msg, RADIUS_ATTR_CONNECT_INFO,
				 buf, strlen(buf))) {
		printf("Could not add Connect-Info\n");
		goto fail;
	}

	if (eap && !radius_msg_add_eap(msg, eap, len)) {
		printf("Could not add EAP-Message\n");
		goto fail;
	}

	/* State attribute must be copied if and only if this packet is
	 * Access-Request reply to the previous Access-Challenge */
	if (sta->last_recv_radius && sta->last_recv_radius->hdr->code ==
	    RADIUS_CODE_ACCESS_CHALLENGE) {
		int res = radius_msg_copy_attr(msg, sta->last_recv_radius,
					       RADIUS_ATTR_STATE);
		if (res < 0) {
			printf("Could not copy State attribute from previous "
			       "Access-Challenge\n");
			goto fail;
		}
		if (res > 0) {
			HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
				      "  Copied RADIUS State Attribute\n");
		}
	}

	radius_client_send(hapd, msg, RADIUS_AUTH);
	return;

 fail:
	radius_msg_free(msg);
	free(msg);
}


static char *eap_type_text(u8 type)
{
	switch (type) {
	case EAP_TYPE_IDENTITY: return "Identity";
	case EAP_TYPE_NOTIFICATION: return "Notification";
	case EAP_TYPE_NAK: return "Nak";
	case EAP_TYPE_MD5_CHALLENGE: return "MD5-Challenge";
	case EAP_TYPE_ONE_TIME_PASSWORD: return "One-Time Password";
	case EAP_TYPE_GENERIC_TOKEN_CARD: return "Generic Token Card";
	case EAP_TYPE_TLS: return "TLS";
	case EAP_TYPE_TTLS: return "TTLS";
	case EAP_TYPE_PEAP: return "PEAP";
	default: return "Unknown";
	}
}


static void handle_eap_response(hostapd *hapd, struct sta_info *sta,
				struct eap_hdr *eap, u8 *data, size_t len)
{
	u8 type;

	assert(sta->eapol_sm != NULL);

	if (eap->identifier != sta->eapol_sm->currentId) {
		printf("EAP Identifier of the Response-Identity from " MACSTR
		       " does not match (was %d, expected %d)\n",
		       MAC2STR(sta->addr), eap->identifier,
		       sta->eapol_sm->currentId);
		return;
	}

	if (len < 1) {
		printf("   too short response data\n");
		return;
	}

	if (sta->last_eap_supp != NULL)
		free(sta->last_eap_supp);
	sta->last_eap_supp_len = sizeof(*eap) + len;
	sta->last_eap_supp = (u8 *) malloc(sta->last_eap_supp_len);
	if (sta->last_eap_supp == NULL) {
		printf("Could not alloc memory for last EAP Response\n");
		return;
	}
	memcpy(sta->last_eap_supp, eap, sizeof(*eap));
	memcpy(sta->last_eap_supp + sizeof(*eap), data, len);

	type = data[0];
	data++;
	len--;

	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
		       HOSTAPD_LEVEL_DEBUG, "received EAP packet (code=%d "
		       "id=%d len=%d) from STA: EAP Response-%s (%d)",
		       eap->code, eap->identifier, ntohs(eap->length),
		       eap_type_text(type), type);

	/* TODO: IEEE 802.1aa/D4: should use auth_pae.initialEAPMsg to check
	 * which EAP packet is accepted as response; currently, hostapd only
	 * supports EAP Response-Identity, so this can be hardcoded */
	if (type == EAP_TYPE_IDENTITY) {
		char *buf, *pos;
		int i;
		buf = malloc(4 * len + 1);
		if (buf) {
			pos = buf;
			for (i = 0; i < len; i++) {
				if (data[i] >= 32 && data[i] < 127)
					*pos++ = data[i];
				else {
					snprintf(pos, 5, "{%02x}", data[i]);
					pos += 4;
				}
			}
			*pos = '\0';
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_IEEE8021X,
				       HOSTAPD_LEVEL_DEBUG,
				       "STA identity '%s'", buf);
			free(buf);
		}

		sta->eapol_sm->auth_pae.rxInitialRsp = TRUE;

		/* Save station identity for future RADIUS packets */
		if (sta->identity)
			free(sta->identity);
		sta->identity = (u8 *) malloc(len);
		if (sta->identity) {
			memcpy(sta->identity, data, len);
			sta->identity_len = len;
		}
	} else {
		if (type != EAP_TYPE_NAK)
			sta->eapol_sm->be_auth.
				backendNonNakResponsesFromSupplicant++;
		sta->eapol_sm->be_auth.rxResp = TRUE;
	}
}


/* Process incoming EAP packet from Supplicant */
static void handle_eap(hostapd *hapd, struct sta_info *sta, u8 *buf,
		       size_t len)
{
	struct eap_hdr *eap;
	u16 eap_len;

	if (len < sizeof(*eap)) {
		printf("   too short EAP packet\n");
		return;
	}

	eap = (struct eap_hdr *) buf;

	eap_len = ntohs(eap->length);
	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "   EAP: code=%d identifier=%d length=%d",
		      eap->code, eap->identifier, eap_len);
	if (eap_len < sizeof(*eap)) {
		printf("   Invalid EAP length\n");
		return;
	} else if (eap_len > len) {
		printf("   Too short frame to contain this EAP packet\n");
		return;
	} else if (eap_len < len) {
		printf("   Ignoring %d extra bytes after EAP packet\n",
		       len - eap_len);
	}

	eap_len -= sizeof(*eap);

	switch (eap->code) {
	case EAP_CODE_REQUEST:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, " (request)\n");
		return;
	case EAP_CODE_RESPONSE:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, " (response)\n");
		handle_eap_response(hapd, sta, eap, (u8 *) (eap + 1), eap_len);
		break;
	case EAP_CODE_SUCCESS:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, " (success)\n");
		return;
	case EAP_CODE_FAILURE:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, " (failure)\n");
		return;
	default:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, " (unknown code)\n");
		return;
	}
}


/* Process the EAPOL frames from the Supplicant */
void ieee802_1x_receive(hostapd *hapd, u8 *sa, u8 *buf, size_t len)
{
	struct sta_info *sta;
	struct ieee802_1x_hdr *hdr;
	u16 datalen;

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: %d bytes from " MACSTR "\n", len,
		      MAC2STR(sa));
	sta = ap_get_sta(hapd, sa);
	if (!sta) {
		printf("   no station information available\n");
		return;
	}

	if (len < sizeof(*hdr)) {
		printf("   too short IEEE 802.1X packet\n");
		return;
	}

	hdr = (struct ieee802_1x_hdr *) buf;
	datalen = ntohs(hdr->length);
	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "   IEEE 802.1X: version=%d type=%d length=%d\n",
		      hdr->version, hdr->type, datalen);

	if (len - sizeof(*hdr) < datalen) {
		printf("   frame too short for this IEEE 802.1X packet\n");
		return;
	}
	if (len - sizeof(*hdr) > datalen) {
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
			      "   ignoring %d extra octets after IEEE 802.1X "
			      "packet\n", len - sizeof(*hdr) - datalen);
	}

	if (!sta->eapol_sm) {
		sta->eapol_sm = eapol_sm_alloc(hapd, sta);
		if (!sta->eapol_sm)
			return;
	}

	/* since we support version 1, we can ignore version field and proceed
	 * as specified in version 1 standard [IEEE Std 802.1X-2001, 7.5.5] */

	switch (hdr->type) {
	case IEEE802_1X_TYPE_EAP_PACKET:
		handle_eap(hapd, sta, (u8 *) (hdr + 1), datalen);
		break;

	case IEEE802_1X_TYPE_EAPOL_START:
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG, "received EAPOL-Start "
			       "from STA");
		sta->eapol_sm->auth_pae.eapStart = TRUE;
		eapol_sm_step(sta->eapol_sm);
		break;

	case IEEE802_1X_TYPE_EAPOL_LOGOFF:
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG, "received EAPOL-Logoff "
			       "from STA");
		sta->acct_terminate_cause =
			RADIUS_ACCT_TERMINATE_CAUSE_USER_REQUEST;
		sta->eapol_sm->auth_pae.eapLogoff = TRUE;
		eapol_sm_step(sta->eapol_sm);
		break;

	case IEEE802_1X_TYPE_EAPOL_KEY:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, "   EAPOL-Key\n");
		if (!(sta->flags & WLAN_STA_AUTHORIZED)) {
			printf("   Dropped key data from unauthorized "
			       "Supplicant\n");
			break;
		}
		break;

	case IEEE802_1X_TYPE_EAPOL_ENCAPSULATED_ASF_ALERT:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
			      "   EAPOL-Encapsulated-ASF-Alert\n");
		/* TODO: implement support for this; show data */
		break;

	default:
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
			      "   unknown IEEE 802.1X packet type\n");
		break;
	}

	eapol_sm_step(sta->eapol_sm);
}


void ieee802_1x_new_station(hostapd *hapd, struct sta_info *sta)
{
	if (!hapd->conf->ieee802_1x)
		return;

	if (sta->eapol_sm) {
		sta->eapol_sm->portEnabled = TRUE;
		eapol_sm_step(sta->eapol_sm);
		return;
	}

	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
		       HOSTAPD_LEVEL_DEBUG, "start authentication");
	sta->eapol_sm = eapol_sm_alloc(hapd, sta);
	sta->eapol_sm->portEnabled = TRUE;
}


void ieee802_1x_free_station(struct sta_info *sta)
{
	if (sta->last_recv_radius) {
		radius_msg_free(sta->last_recv_radius);
		free(sta->last_recv_radius);
	}

	if (sta->last_eap_supp)
		free(sta->last_eap_supp);
	if (sta->last_eap_radius)
		free(sta->last_eap_radius);

	if (sta->identity)
		free(sta->identity);

	free(sta->eapol_key_sign);
	free(sta->eapol_key_crypt);

	eapol_sm_free(sta->eapol_sm);
}


static void ieee802_1x_decapsulate_radius(hostapd *hapd, struct sta_info *sta)
{
	char *eap;
	size_t len;
	struct eap_hdr *hdr;
	int eap_type = -1;
	char buf[64];
	struct radius_msg *msg;

	if (sta->last_recv_radius == NULL)
		return;

	msg = sta->last_recv_radius;

	eap = radius_msg_get_eap(msg, &len);
	if (eap == NULL) {
		/* draft-aboba-radius-rfc2869bis-20.txt, Chap. 2.6.3:
		 * RADIUS server SHOULD NOT send Access-Reject/no EAP-Message
		 * attribute */
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_WARNING, "could not extract "
			       "EAP-Message from RADIUS message");
		free(sta->last_eap_radius);
		sta->last_eap_radius = NULL;
		sta->last_eap_radius_len = 0;
		return;
	}

	if (len < sizeof(*hdr)) {
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_WARNING, "too short EAP packet "
			       "received from authentication server");
		free(eap);
		return;
	}

	if (len > sizeof(*hdr))
		eap_type = eap[sizeof(*hdr)];

	hdr = (struct eap_hdr *) eap;
	switch (hdr->code) {
	case EAP_CODE_REQUEST:
		snprintf(buf, sizeof(buf), "EAP-Request-%s (%d)",
			 eap_type >= 0 ? eap_type_text(eap_type) : "??",
			 eap_type);
		break;
	case EAP_CODE_RESPONSE:
		snprintf(buf, sizeof(buf), "EAP Response-%s (%d)",
			 eap_type >= 0 ? eap_type_text(eap_type) : "??",
			 eap_type);
		break;
	case EAP_CODE_SUCCESS:
		snprintf(buf, sizeof(buf), "EAP Success");
		break;
	case EAP_CODE_FAILURE:
		snprintf(buf, sizeof(buf), "EAP Failure");
		break;
	default:
		snprintf(buf, sizeof(buf), "unknown EAP code");
		break;
	}
	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
		       HOSTAPD_LEVEL_DEBUG, "decapsulated EAP packet (code=%d "
		       "id=%d len=%d) from RADIUS server: %s",
		      hdr->code, hdr->identifier, ntohs(hdr->length), buf);

	sta->eapol_sm->be_auth.idFromServer = hdr->identifier;

	if (sta->last_eap_radius)
		free(sta->last_eap_radius);
	sta->last_eap_radius = eap;
	sta->last_eap_radius_len = len;
}


static void ieee802_1x_get_keys(hostapd *hapd, struct sta_info *sta,
				struct radius_msg *msg, struct radius_msg *req,
				u8 *shared_secret, size_t shared_secret_len)
{
	struct radius_ms_mppe_keys *keys;

	keys = radius_msg_get_ms_keys(msg, req, shared_secret,
				      shared_secret_len);

	if (keys) {
		if (HOSTAPD_DEBUG_COND(HOSTAPD_DEBUG_MINIMAL) && keys->send) {
			size_t i;
			printf("MS-MPPE-Send-Key (len=%d):", keys->send_len);
			for (i = 0; i < keys->send_len; i++)
				printf(" %02x", keys->send[i]);
			printf("\n");
		}
		if (HOSTAPD_DEBUG_COND(HOSTAPD_DEBUG_MINIMAL) && keys->recv) {
			size_t i;
			printf("MS-MPPE-Recv-Key (len=%d):", keys->recv_len);
			for (i = 0; i < keys->recv_len; i++)
				printf(" %02x", keys->recv[i]);
			printf("\n");
		}

		if (keys->send && keys->recv) {
			free(sta->eapol_key_sign);
			free(sta->eapol_key_crypt);
			sta->eapol_key_sign = keys->send;
			sta->eapol_key_sign_len = keys->send_len;
			sta->eapol_key_crypt = keys->recv;
			sta->eapol_key_crypt_len = keys->recv_len;
			if (hapd->default_wep_key ||
			    hapd->conf->individual_wep_key_len > 0)
				sta->eapol_sm->keyAvailable = TRUE;
		} else {
			free(keys->send);
			free(keys->recv);
		}
		free(keys);
	}
}


/* Process the RADIUS frames from Authentication Server */
static RadiusRxResult
ieee802_1x_receive_auth(hostapd *hapd,
			struct radius_msg *msg, struct radius_msg *req,
			u8 *shared_secret, size_t shared_secret_len,
			void *data)
{
	struct sta_info *sta;
	u32 session_timeout, termination_action;
	int session_timeout_set;

	sta = ap_get_sta_radius_identifier(hapd, msg->hdr->identifier);
	if (sta == NULL) {
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, "IEEE 802.1X: Could not "
			      "find matching station for this RADIUS "
			      "message\n");
		return RADIUS_RX_UNKNOWN;
	}

	/* RFC 2869, Ch. 5.13: valid Message-Authenticator attribute MUST be
	 * present when packet contains an EAP-Message attribute */
	if (msg->hdr->code == RADIUS_CODE_ACCESS_REJECT &&
	    radius_msg_get_attr(msg, RADIUS_ATTR_MESSAGE_AUTHENTICATOR, NULL,
				0) < 0 &&
	    radius_msg_get_attr(msg, RADIUS_ATTR_EAP_MESSAGE, NULL, 0) < 0) {
		HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL, "Allowing RADIUS "
			      "Access-Reject without Message-Authenticator "
			      "since it does not include EAP-Message\n");
	} else if (radius_msg_verify(msg, shared_secret, shared_secret_len,
				     req)) {
		printf("Incoming RADIUS packet did not have correct "
		       "Message-Authenticator - dropped\n");
		return RADIUS_RX_UNKNOWN;
	}

	if (msg->hdr->code != RADIUS_CODE_ACCESS_ACCEPT &&
	    msg->hdr->code != RADIUS_CODE_ACCESS_REJECT &&
	    msg->hdr->code != RADIUS_CODE_ACCESS_CHALLENGE) {
		printf("Unknown RADIUS message code\n");
		return RADIUS_RX_UNKNOWN;
	}

	sta->radius_identifier = -1;
	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "RADIUS packet matching with station " MACSTR "\n",
		      MAC2STR(sta->addr));

	if (sta->last_recv_radius) {
		radius_msg_free(sta->last_recv_radius);
		free(sta->last_recv_radius);
	}

	sta->last_recv_radius = msg;

	session_timeout_set =
		!radius_msg_get_attr_int32(msg, RADIUS_ATTR_SESSION_TIMEOUT,
					   &session_timeout);
	if (radius_msg_get_attr_int32(msg, RADIUS_ATTR_TERMINATION_ACTION,
				      &termination_action))
		termination_action = RADIUS_TERMINATION_ACTION_DEFAULT;

	switch (msg->hdr->code) {
	case RADIUS_CODE_ACCESS_ACCEPT:
		/* draft-congdon-radius-8021x-22.txt, Ch. 3.17 */
		if (session_timeout_set &&
			termination_action ==
		    RADIUS_TERMINATION_ACTION_RADIUS_REQUEST) {
			sta->eapol_sm->reauth_timer.reAuthPeriod =
				session_timeout;
		} else if (session_timeout_set)
			ap_sta_session_timeout(hapd, sta, session_timeout);

		sta->eapol_sm->be_auth.aSuccess = TRUE;
		ieee802_1x_get_keys(hapd, sta, msg, req, shared_secret,
				    shared_secret_len);
		break;
	case RADIUS_CODE_ACCESS_REJECT:
		sta->eapol_sm->be_auth.aFail = TRUE;
		break;
	case RADIUS_CODE_ACCESS_CHALLENGE:
		if (session_timeout_set) {
			/* RFC 2869, Ch. 2.3.2
			 * draft-congdon-radius-8021x-22.txt, Ch. 3.17 */
			sta->eapol_sm->be_auth.suppTimeout = session_timeout;
		}
		sta->eapol_sm->be_auth.aReq = TRUE;
		break;
	}

	ieee802_1x_decapsulate_radius(hapd, sta);

	eapol_sm_step(sta->eapol_sm);

	return RADIUS_RX_QUEUED;
}


/* Handler for EAPOL Backend Authentication state machine sendRespToServer.
 * Forward the EAP Response from Supplicant to Authentication Server. */
void ieee802_1x_send_resp_to_server(hostapd *hapd, struct sta_info *sta)
{
	if (hapd->conf->minimal_eap)
		minimal_auth_serv(hapd, sta, sta->last_eap_supp,
				  sta->last_eap_supp_len);
	else
		ieee802_1x_encapsulate_radius(hapd, sta, sta->last_eap_supp,
					      sta->last_eap_supp_len);
}


void ieee802_1x_set_port_enabled(hostapd *hapd, struct sta_info *sta,
				 int enabled)
{
	if (!sta->eapol_sm)
		return;

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: station " MACSTR " port %s\n",
		      MAC2STR(sta->addr), enabled ? "enabled" : "disabled");
	sta->eapol_sm->portEnabled = enabled ? TRUE : FALSE;
	eapol_sm_step(sta->eapol_sm);
}


#ifdef HOSTAPD_DUMP_STATE
void ieee802_1x_dump_state(FILE *f, const char *prefix, struct sta_info *sta)
{
	fprintf(f, "%sIEEE 802.1X:\n", prefix);

	if (sta->identity) {
		size_t i;
		fprintf(f, "%sidentity=", prefix);
		for (i = 0; i < sta->identity_len; i++)
			fprint_char(f, sta->identity[i]);
		fprintf(f, "\n");
	}

	fprintf(f, "%scached_packets=%s%s%s\n", prefix,
		sta->last_recv_radius ? "[RX RADIUS]" : "",
		sta->last_eap_radius ? "[EAP RADIUS]" : "",
		sta->last_eap_supp ? "[EAP SUPPLICANT]" : "");

	if (sta->eapol_sm)
		eapol_sm_dump_state(f, prefix, sta->eapol_sm);
}
#endif /* HOSTAPD_DUMP_STATE */


static int ieee802_1x_init_kernel_1x(hostapd *hapd)
{
	/* enable kernel driver support for IEEE 802.1X */
	if (hostap_ioctl_prism2param(hapd, PRISM2_PARAM_IEEE_802_1X, 1)) {
		printf("Could not setup IEEE 802.1X support in kernel driver."
		       "\n");
		return -1;
	}

	/* use host driver implementation of encryption to allow
	 * individual keys and passing plaintext EAPOL frames */
	if (hostap_ioctl_prism2param(hapd, PRISM2_PARAM_HOST_DECRYPT, 1) ||
	    hostap_ioctl_prism2param(hapd, PRISM2_PARAM_HOST_ENCRYPT, 1)) {
		printf("Could not setup host-based encryption in kernel "
		       "driver.\n");
		return -1;
	}

	return 0;
}


int ieee802_1x_init(hostapd *hapd)
{
	if (hapd->conf->ieee802_1x && ieee802_1x_init_kernel_1x(hapd))
		return -1;

	if (radius_client_register(hapd, RADIUS_AUTH, ieee802_1x_receive_auth,
				   NULL))
		return -1;

	return 0;
}


void ieee802_1x_deinit(hostapd *hapd)
{
}


void ieee802_1x_new_auth_session(hostapd *hapd, struct sta_info *sta)
{
	if (!sta->last_recv_radius)
		return;

	HOSTAPD_DEBUG(HOSTAPD_DEBUG_MINIMAL,
		      "IEEE 802.1X: station " MACSTR " - new auth session, "
		      "clearing State\n", MAC2STR(sta->addr));

	radius_msg_free(sta->last_recv_radius);
	free(sta->last_recv_radius);
	sta->last_recv_radius = NULL;
}
