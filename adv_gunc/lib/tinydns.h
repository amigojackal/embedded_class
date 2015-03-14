/* 
 * Resolved name service with specified type, such as T_MX or T_A is supported
 * 
 * To make, with options -lresolv
 */
#ifndef _TINYDNS_H
#define _TINYDNS_H

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
struct ans_sec{
	unsigned char name[512];	/* Formated query name */
	u_int16_t type;			/* T_MX, or T_A ... */
	u_int16_t class;		/* Protocol type, IPV4 */
	u_int32_t ttl;			/* Timeout. by seconds */
	u_int16_t rdatalen;		/* Caller should not use */
	u_int8_t payload[511];		/* Formated payload */
	u_int8_t _size;			/* Size of this section within packet */
	struct in_addr _in_addr;	/* ip address if @class is T_A */
	struct ans_sec  *next;
};
/*
 * Query name resolver.
 * @qstr - Query string, such as "yahoo.com.tw"
 * @type - Type of record, available value is T_A,T_MX.
 * Return:
 *	Return a pointer struct ans_sec. NULL as failure.
 * Caller should free with ns_free() to release memory when need not to use.
 */
extern struct ans_sec *ns_query(const char *qstr, int type);
extern void dump_ans_sec(struct ans_sec *as);
extern void ns_free(struct ans_sec *as);
#endif //_TINYDNS_H
