/* 
 * Resolved name service with specified type, such as T_MX or T_A is supported
 * 
 * To make, with options -lresolv
 */
#include "tinydns.h"

struct dns_head{
	u_int16_t id;
	u_int16_t flags;
	u_int16_t qrr;
	u_int16_t arr;
	u_int16_t authrr;
	u_int16_t addrr;
};
#define DNSHEADLEN	12
struct query_sec{
	unsigned char name[512];
	u_int16_t type;
	u_int16_t class;
	u_int8_t _size;
};

inline int
get_head_qrr(struct dns_head *dh){
	return ntohs(dh->qrr);
}

inline int 
get_head_arr(struct dns_head *dh){
	return ntohs(dh->arr);
}

inline int
get_head_authrr(struct dns_head *dh){
	return ntohs(dh->authrr);
}

inline int
get_head_addrr(struct dns_head *dh){
	return ntohs(dh->addrr);
}

void
dump_dns_head(struct dns_head *dh){
	int cnv;
	printf("Id:%d\n",ntohs(dh->id));
	cnv = ntohs(dh->flags);
	
	printf("Flag:%s\n", cnv & 0x1000?"Request":"Response");
	printf("\topcode:%d\n",(cnv > 11 )& 0xF);
	printf("\tAnswer RR:%d,Authority RR:%d,Additional RR:%d\n",
		ntohs(dh->arr),ntohs(dh->authrr),ntohs(dh->addrr));
	return;
}
/*
 * Parse the name of qeury which formated from DNS, length/label or a
 * compressed pointer.
 * 
 * @s - Payload of DNS result which from res_query() Library.
 * @p - The printer points to Question-Name format
 * @o - Output the data which formated to strings for human visible.
 *
 * Return: Return the length of which formated.
 */
int
parse_name(const char *s, const char *p, unsigned char *o)
{
	char i;
	int of = 0, pof;
	
	i = p[0];
	while(i){
		if (i & 0xc0){ /*The first 2 bit indicates compressed. */
			
			/* The following 14 bits is offset from payload. */
			pof = ntohs((*((u_int16_t *)(p+of))) & htons(0x3FFF) );
			//printf("Point to:%x as %x\n", *(u_int16_t *)p, pof);
			parse_name(s, s + pof, o);
			return of + 2; //+2 is lenght and offset two octets
		}

		strncat(o, p+of+1, i);
		strcat(o,".");
		//fprintf(stderr, "%d:%s\n", i, o);
		of += i+1;
		i = p[of];
	}
	return of+1;
}

int
parse_query_sec(const char *s, const char *p, struct query_sec *qs)
{
	int of;
	
	of = parse_name(s, p, qs->name);
	//printf("Parse Name:%s\n", qs->name);
	qs->type = ntohs(*(u_int16_t *)(p+of));
	//printf("Type:%x,",qs->type);
	qs->class = ntohs(*(u_int16_t *)(p+of+2));
	//printf("Class:%x\n", qs->class);
	return qs->_size = of + 4;
}

void
dump_query_sec(struct query_sec *qs){
	printf("Parse Name:%s, Type:%x, Class:%x\n",
		qs->name, qs->type, qs->class);
}

void 
dump_hex(const unsigned char *s, int len){
	int c, enl = 0;
	for (c = 0; c < len; c++) {
		printf("%x ", s[c]);
		if (enl++ == 16) {
			printf("\n");
			enl = 0;
		}
	}
	printf("\n");
}

int
parse_ans_sec(const char *s, const char *p, struct ans_sec *as){
	int of;
	
	of = parse_name(s, p, as->name);
	as->type = ntohs(*(u_int16_t *)(p+of));
	as->class = ntohs(*(u_int16_t *)(p+of+2));
	as->ttl = ntohl(*(u_int32_t *)(p+of+4));
	as->rdatalen = ntohs(*(u_int16_t *)(p+of+8));
	
	
	switch (as->type){
	struct in_addr in;
	case T_MX:
		parse_name(s, p + of + 12, as->payload);
		sprintf(as->payload+strlen(as->payload), " reference = %d",
			ntohs(*(u_int16_t *)(p+of+10)));
		break;
	case T_A:
		//dump_hex(p+of+10-2, 8);
		//printf("ip:%p,%x, ",p+of+10,*(struct in_addr *)(p+of+10));
		memcpy(&in, p+of+10, 4);
		//printf(" cv:%x, ", in);
		//strcpy(as->payload, inet_ntoa(*(struct in_addr *)(p+of+10)));
		strcpy(as->payload, inet_ntoa(in));
		//printf("to: %s\n", as->payload);
	};
	
	//printf("[%s]\n", as->payload);
	//printf("Len:%d\n", as->_size = of + 10 + as->rdatalen);
	return as->_size = of + 10 + as->rdatalen; //size of anwser section
}

void
__dump_ans_sec(struct ans_sec *as)
{
	printf("Record name:%s\n", as->name);
	printf("Type:%x,", as->type);
	printf("Class:%x,", as->class);
	printf("TTL:%x,", as->ttl);
	printf("rDataLen:%x\n", as->rdatalen);
	printf("\tPayload:%s,", as->payload);
	printf("Size of section:%x\n", as->_size);
}

void
dump_ans_sec(struct ans_sec *as)
{
	printf("--------------------------\n");
	while(as){
		__dump_ans_sec(as);
		as = as->next;
	}
	printf("--------------------------\n");
}

void
ns_free(struct ans_sec *as)
{
	struct ans_sec *n = NULL;
	
	while (as) {
		n = as;
		as = as->next;
		free(n);
	}
}

struct ans_sec *
ns_query(const char *qstr, int type){
	struct dns_head *dh;
	struct query_sec qs;
	struct ans_sec *asn = NULL, *ashead = NULL;
	char ans[512];
	int v, i, of, arrs[3], qrr;
	
	res_init();
	v = res_query(qstr, ns_c_in, type, ans, sizeof(ans));
	if (v == -1)
		return NULL;
	
	dh = (struct dns_head *)ans;
	qrr = get_head_qrr(dh);
	arrs[0] = get_head_arr(dh);
	arrs[1] = get_head_authrr(dh);
	arrs[2] = get_head_addrr(dh);
	
	of = parse_query_sec(ans, dh + 1, &qs);
	//dump_query_sec(&qs);
	
	for (i = 0;i < 3; i++) {
		for (v = 0;v < arrs[i]; v++) {
			asn = malloc(sizeof(struct ans_sec));
			bzero(asn, sizeof(struct ans_sec));
			asn->next = ashead;
			of += parse_ans_sec(ans, ans + DNSHEADLEN + of, asn);
			ashead = asn;
		}
	}
	return ashead;
}
/*
int
main(int argc, char *argv[]){
	struct ans_sec *as, *n;
	
	if (argc < 2)
		return 0;
	
	as = ns_query(argv[1], T_MX);
	if (as == NULL) {
		printf("Not found %s\n",argv[1]);
		return 0;
	}
	n = as;
	while(as){
		if (as->type == T_A){
			printf("%s\n",as->payload);
		}
		if (as->type == T_MX){
			printf("MX:%s\n",as->payload);
		}
		as = as->next;
	}
	ns_free(n);
}
*/
