
/*
 * Copyright 2001-2003, Broadcom Corporation
 * All Rights Reserved.
 * 
 * THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
 * KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
 * SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
 *
 * $Id$
 */
/*
 * NVRAM variable manipulation
 *
 * Copyright (C) 2001 Broadcom Corporation
 *
 * $Id: common.h,v 1.2 2004/01/05 05:39:18 Cheni_Shen Exp $
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* cprintf to stdout */
#define cprintf printf

struct variable {
	char *name;
	char *longname;
	int (*validate)(char *value, struct variable *v);
	char **argv;	
	int nullok;
	int event;
};

struct action
{
      char *name;
      char **in_name;
      char **in_var;
      char **out_name;
      char **out_var; 
      char **group_tag;     
      int (*callback)(void);
};

struct svcLink
{
      char *serviceId;
      char *serviceType;
      struct variable *variables;
      struct action *actions;
};

#define ARGV(args...) ((char *[]) { args, NULL })


#ifdef __cplusplus
extern "C" {
#endif

/* API export for UPnP function */
void InitVariables(void);
int LookupServiceId(char *serviceId);
char *GetServiceId(int sid);
struct action *GetActions(int sid);
struct variable *GetVariables(int sid);
char *GetServiceType(int sid);
struct action *CheckActions(int sid, char *name);
int CheckVariables(int sid, char *name, char *var);
char *GetVariable(int sid, char *name);
void SetVariable(int sid, char *name, char *value);

struct variable *LookupGroupVariables(int sid, char *groupName);
int CheckGroupVariables(int sid, struct variable *gvs, char *name, char *var);
void SetGroupVariable(int sid, struct variable *gvs, char *name, char *value, char *action);
char *GetGroupVariable(int sid, struct variable *gvs, char *name);


#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H_ */
