/*
 * NVRAM variable manipulation (common)
 *
 * Copyright 2003, Broadcom Corporation
 * All Rights Reserved.                
 *                                     
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;   
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior      
 * written permission of Broadcom Corporation.                            
 *
 * $Id: nvram.c,v 1.32 2003/05/07 19:07:40 mhuang Exp $
 */
#include <linux/config.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <typedefs.h>
//#include <osl.h>
//#include <bcmendian.h>
#include <bcmnvram.h>
#include <bcmutils.h>
#include <sbsdram.h>

#define MALLOC(s) kmalloc(s, GFP_KERNEL)
#define MFREE(p,s) kfree(p)
#define htol32(i) (i)
#define printf printk

extern struct nvram_tuple * _nvram_realloc(struct nvram_tuple *t, const char *name, const char *value);
extern void _nvram_free(struct nvram_tuple *t);
extern int _nvram_read(void *buf);

char * _nvram_get(const char *name);
int _nvram_set(const char *name, const char *value);
int _nvram_unset(const char *name);
int _nvram_getall(char *buf, int count);
int _nvram_commit(struct nvram_header *header);
int _nvram_init(void);
void _nvram_exit(void);

static struct nvram_tuple * nvram_hash[257] = { NULL };
static struct nvram_tuple * nvram_dead = NULL;

/* Free all tuples. Should be locked. */
static void
nvram_free(void)
{
	uint i;
	struct nvram_tuple *t, *next;

	/* Free hash table */
	for (i = 0; i < ARRAYSIZE(nvram_hash); i++) {
		for (t = nvram_hash[i]; t; t = next) {
			next = t->next;
			_nvram_free(t);
		}
		nvram_hash[i] = NULL;
	}

	/* Free dead table */
	for (t = nvram_dead; t; t = next) {
		next = t->next;
		_nvram_free(t);
	}
	nvram_dead = NULL;

	/* Indicate to per-port code that all tuples have been freed */
	_nvram_free(NULL);
}

/* String hash */
static INLINE uint
hash(const char *s)
{
	uint hash = 0;

	while (*s)
		hash = 31 * hash + *s++;

	return hash;
}

/* (Re)initialize the hash table. Should be locked. */
static int
nvram_rehash(struct nvram_header *header)
{
	char buf[] = "0xXXXX", *name, *value, *end, *eq;

	/* (Re)initialize hash table */
	nvram_free();

	/* Parse and set "name=value\0 ... \0\0" */
	name = (char *) &header[1];
	end = (char *) header + NVRAM_SPACE - 2;
	end[0] = end[1] = '\0';
	for (; *name; name = value + strlen(value) + 1) {
		if (!(eq = strchr(name, '=')))
			break;
		*eq = '\0';
		value = eq + 1;
		_nvram_set(name, value);
		*eq = '=';
	}

	/* Set special SDRAM parameters */
	if (!_nvram_get("sdram_init")) {
		sprintf(buf, "0x%04X", (uint16)(header->crc_ver_init >> 16));
		_nvram_set("sdram_init", buf);
	}
	if (!_nvram_get("sdram_config")) {
		sprintf(buf, "0x%04X", (uint16)(header->config_refresh & 0xffff));
		_nvram_set("sdram_config", buf);
	}
	if (!_nvram_get("sdram_refresh")) {
		sprintf(buf, "0x%04X", (uint16)((header->config_refresh >> 16) & 0xffff));
		_nvram_set("sdram_refresh", buf);
	}

	{
	char *proto;
	// added by Chen-I for bypass fast route flag
	proto = _nvram_get("wan_proto");

	if (!(strncmp(proto, "dhcp", 4)==0 || strncmp(proto, "bigpond", 7)==0))
	{
		set_bypass_fast_rt();	
	}	
	}
	return 0;
}

/* Get the value of an NVRAM variable. Should be locked. */
char *
_nvram_get(const char *name)
{
	uint i;
	struct nvram_tuple *t;
	char *value;

	if (!name)
		return NULL;

	/* Hash the name */
	i = hash(name) % ARRAYSIZE(nvram_hash);

	/* Find the associated tuple in the hash table */
	for (t = nvram_hash[i]; t && strcmp(t->name, name); t = t->next);

	value = t ? t->value : NULL;

	return value;
}

/* Get the value of an NVRAM variable. Should be locked. */
int
_nvram_set(const char *name, const char *value)
{
	uint i;
	struct nvram_tuple *t, *u, **prev;


	//printk("s: %s %d\n", value, strlen(value));

	/* Hash the name */
	i = hash(name) % ARRAYSIZE(nvram_hash);

	/* Find the associated tuple in the hash table */
	for (prev = &nvram_hash[i], t = *prev; t && strcmp(t->name, name); prev = &t->next, t = *prev);

	/* (Re)allocate tuple */
	if (!(u = _nvram_realloc(t, name, value)))
		return -12; /* -ENOMEM */

	/* Value reallocated */
	if (t && t == u)
		return 0;

	/* Move old tuple to the dead table */
	if (t) {
		*prev = t->next;
		t->next = nvram_dead;
		nvram_dead = t;
	}

	/* Add new tuple to the hash table */
	u->next = nvram_hash[i];
	nvram_hash[i] = u;

	return 0;
}

/* Unset the value of an NVRAM variable. Should be locked. */
int
_nvram_unset(const char *name)
{
	uint i;
	struct nvram_tuple *t, **prev;

	if (!name)
		return 0;

	/* Hash the name */
	i = hash(name) % ARRAYSIZE(nvram_hash);

	/* Find the associated tuple in the hash table */
	for (prev = &nvram_hash[i], t = *prev; t && strcmp(t->name, name); prev = &t->next, t = *prev);

	/* Move it to the dead table */
	if (t) {
		*prev = t->next;
		t->next = nvram_dead;
		nvram_dead = t;
	}

	return 0;
}

/* Get all NVRAM variables. Should be locked. */
int
_nvram_getall(char *buf, int count)
{
	uint i;
	struct nvram_tuple *t;
	int len = 0;

	memset(buf, 0, count);

	/* Write name=value\0 ... \0\0 */
	for (i = 0; i < ARRAYSIZE(nvram_hash); i++) {
		for (t = nvram_hash[i]; t; t = t->next) {
			if ((count - len) > (strlen(t->name) + 1 + strlen(t->value) + 1))
			{
				// added by Joey for value=<NULL>
				if (strlen(t->value)==0)	
					len += sprintf(buf + len, "%s=", t->name) + 1;
				else					
					len += sprintf(buf + len, "%s=%s", t->name, t->value) + 1;
			}

			else
				break;
		}
	}

	return 0;
}

/* Regenerate NVRAM. Should be locked. */
int
_nvram_commit(struct nvram_header *header)
{
	char *init, *config, *refresh;
	char *ptr, *end;
	int i;
	struct nvram_tuple *t;
	struct nvram_header tmp;
	uint8 crc;

	/* Regenerate header */
	header->magic = NVRAM_MAGIC;
	header->crc_ver_init = (NVRAM_VERSION << 8);
	if (!(init = _nvram_get("sdram_init")) ||
	    !(config = _nvram_get("sdram_config")) ||
	    !(refresh = _nvram_get("sdram_refresh"))) {
		header->crc_ver_init |= SDRAM_INIT << 16;
		header->config_refresh = SDRAM_CONFIG;
		header->config_refresh |= SDRAM_REFRESH << 16;
	} else {
		header->crc_ver_init |= (simple_strtoul(init, NULL, 0) & 0xffff) << 16;
		header->config_refresh = simple_strtoul(config, NULL, 0) & 0xffff;
		header->config_refresh |= (simple_strtoul(refresh, NULL, 0) & 0xffff) << 16;
	}
	header->reserved = 0;

	/* Clear data area */
	ptr = (char *) header + sizeof(struct nvram_header);
	memset(ptr, 0, NVRAM_SPACE - sizeof(struct nvram_header));

	/* Leave space for a double NUL at the end */
	end = (char *) header + NVRAM_SPACE - 2;

	/* Write out all tuples */
	for (i = 0; i < ARRAYSIZE(nvram_hash); i++) {
		for (t = nvram_hash[i]; t; t = t->next) {
			if ((ptr + strlen(t->name) + 1 + strlen(t->value) + 1) > end)
				break;

			// added by Joey for value=<NULL>
			if (strlen(t->value)==0)	
				ptr += sprintf(ptr, "%s=", t->name) + 1;
			else					
				ptr += sprintf(ptr, "%s=%s", t->name, t->value) + 1;
		}
	}

	/* End with a double NUL */
	ptr += 2;

	/* Set new length */
	header->len = ROUNDUP(ptr - (char *) header, 4);

	/* Little-endian CRC8 over the last 11 bytes of the header */
	tmp.crc_ver_init = htol32(header->crc_ver_init);
	tmp.config_refresh = htol32(header->config_refresh);
	tmp.reserved = htol32(header->reserved);
	crc = crc8((char *) &tmp + 9, sizeof(struct nvram_header) - 9, CRC8_INIT_VALUE);

	/* Continue CRC8 over data bytes */
	crc = crc8((char *) &header[1], header->len - sizeof(struct nvram_header), crc);

	/* Set new CRC8 */
	header->crc_ver_init |= crc;

	/* Reinitialize hash table */
	return nvram_rehash(header);
}

/* Initialize hash table. Should be locked. */
int
_nvram_init(void)
{
	struct nvram_header *header;
	int ret;

	if (!(header = (struct nvram_header *) MALLOC(NVRAM_SPACE))) {
		printf("nvram_init: out of memory\n");
		return -12; /* -ENOMEM */
	}

	if ((ret = _nvram_read(header)) == 0 &&
	    header->magic == NVRAM_MAGIC)
		nvram_rehash(header);

	MFREE(header, NVRAM_SPACE);
	return ret;
}

/* Free hash table. Should be locked. */
void
_nvram_exit(void)
{
	nvram_free();
}
