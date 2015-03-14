#ifndef __NET_H__
#define __NET_H__
extern u_int32_t get_networkip(const char *ifname);
extern int get_ip(const char *ifname, char *buf);
#endif
