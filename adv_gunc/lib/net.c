#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

/* Get IP from interface @ifname
 * Input:
 *	@ifname: name of interface
 * Output:
 *	@buf is converted by inet_ntoa()
 */

int get_ip(const char *ifname, char *buf)
{
	int s, r, ret = -1;
	struct ifreq ifr;
	struct sockaddr_in in;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&ifr, 0, sizeof(struct ifreq));
	strcpy(ifr.ifr_name, ifname);
	r = ioctl(s, SIOCGIFADDR, &ifr);
	close(s);
	if (r < 0){
		return ret;
	}
	memcpy(&in, &ifr.ifr_addr, sizeof(struct sockaddr_in));
	strcpy(buf, (char *)inet_ntoa(in.sin_addr));
	ret = 0;
	return ret;
}

u_int32_t get_networkip(const char *ifname)
{
	int s, r, ret = 0;
	struct ifreq ifr;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&ifr, 0, sizeof(struct ifreq));
	strcpy(ifr.ifr_name, ifname);
	r = ioctl(s, SIOCGIFADDR, &ifr);
	close(s);
	if (r < 0){
		return ret;
	}
	return ((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr.s_addr;
}
