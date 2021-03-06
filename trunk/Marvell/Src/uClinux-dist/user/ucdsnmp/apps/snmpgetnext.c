/*
 * snmpgetnext.c - send snmp GETNEXT requests to a network entity.
 *
 */
/***********************************************************************
	Copyright 1988, 1989, 1991, 1992 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of CMU not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

CMU DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
CMU BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************/
#include <config.h>

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#include <sys/types.h>
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#include <stdio.h>
#include <ctype.h>
#if TIME_WITH_SYS_TIME
# ifdef WIN32
#  include <sys/timeb.h>
# else
#  include <sys/time.h>
# endif
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#if HAVE_WINSOCK_H
#include <winsock.h>
#endif
#if HAVE_NETDB_H
#include <netdb.h>
#endif
#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#include <getopt.h>

#include "asn1.h"
#include "snmp_api.h"
#include "snmp_impl.h"
#include "snmp_client.h"
#include "snmp.h"
#include "mib.h"
#include "system.h"
#include "snmp_parse_args.h"
#include "default_store.h"

#define DS_APP_DONT_FIX_PDUS 0

static void optProc(int argc, char *const *argv, int opt)
{
    switch (opt) {
        case 'C':
            while (*optarg) {
                switch (*optarg++) {
                    case 'f':
                        ds_toggle_boolean(DS_APPLICATION_ID, DS_APP_DONT_FIX_PDUS);
                        break;
                }
            }
            break;
    }
}

void usage(void)
{
  fprintf(stderr,"Usage: snmpgetnext [-Cf]");
  snmp_parse_args_usage(stderr);
  fprintf(stderr," [<objectID> ...]\n\n");
  snmp_parse_args_descriptions(stderr);
  fprintf(stderr, "snmpgetnext specific options\n");
  fprintf(stderr, "  -Cf\t\tDon't fix errors and retry the request.\n");
}

int main(int argc, char *argv[])
{
    struct snmp_session session, *ss;
    struct snmp_pdu *pdu, *response;
    struct variable_list *vars;
    int   arg;
    int   count;
    int   current_name = 0;
    char  *names[128];
    oid   name[MAX_OID_LEN];
    size_t name_length;
    int   status;
    int   failures = 0;

    /* get the common command line arguments */
    arg = snmp_parse_args(argc, argv, &session, "C:", &optProc);

    if (arg >= argc) {
      fprintf(stderr, "Missing object name\n");
      usage();
      exit(1);
    }

    /* get the object names */
    for(; arg < argc; arg++)
      names[current_name++] = argv[arg];

    SOCK_STARTUP;

    /* open an SNMP session */
    ss = snmp_open(&session);
    if (ss == NULL){
      /* diagnose snmp_open errors with the input struct snmp_session pointer */
      snmp_sess_perror("snmpgetnext", &session);
      SOCK_CLEANUP;
      exit(1);
    }

    /* create PDU for GET request and add object names to request */
    pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);

    for(count = 0; count < current_name; count++){
      name_length = MAX_OID_LEN;
      if (snmp_parse_oid(names[count], name, &name_length) == NULL) {
        snmp_perror(names[count]);
        failures++;
      } else
        snmp_add_null_var(pdu, name, name_length);
    }
    if (failures) {
      SOCK_CLEANUP;
      exit(1);
    }

    /* do the request */
retry:
    status = snmp_synch_response(ss, pdu, &response);
    if (status == STAT_SUCCESS){
      if (response->errstat == SNMP_ERR_NOERROR){
        for(vars = response->variables; vars; vars = vars->next_variable)
          print_variable(vars->name, vars->name_length, vars);
        } else {
          fprintf(stderr, "Error in packet.\nReason: %s\n",
                  snmp_errstring(response->errstat));
          if (response->errstat == SNMP_ERR_NOSUCHNAME){
            fprintf(stderr, "This name doesn't exist: ");
          for(count = 1, vars = response->variables;
                vars && count != response->errindex;
                vars = vars->next_variable, count++)
            ;
          if (vars)
            fprint_objid(stderr, vars->name, vars->name_length);
          fprintf(stderr, "\n");
        }

        /* retry if the errored variable was successfully removed */
        if (!ds_get_boolean(DS_APPLICATION_ID, DS_APP_DONT_FIX_PDUS)) {
            pdu = snmp_fix_pdu(response, SNMP_MSG_GETNEXT);
            snmp_free_pdu(response);
            response = NULL;
            if (pdu != NULL)
                goto retry;
        }
      }
    } else if (status == STAT_TIMEOUT){
      fprintf(stderr, "Timeout: No Response from %s.\n", session.peername);
    } else {    /* status == STAT_ERROR */
      snmp_sess_perror("snmpgetnext", ss);
    }

    if (response)
      snmp_free_pdu(response);
    snmp_close(ss);
    SOCK_CLEANUP;
    return 0;
}
