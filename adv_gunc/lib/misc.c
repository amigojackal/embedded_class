#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Return IP address with Network byte oder */
u_int32_t get_random_dot_ip(const char *ips, const char *ipe, char *out)
{
	u_int32_t s, e, n;
	time_t t;
	int r;
	
	time(&t);
	srand((unsigned int)t);
	r = rand();
	s = inet_network(ips);
	e = inet_network(ipe);
	
	if (s > e)
		n = e + r % (s - e + 1);
	else
		n = s + r % (e - s + 1);
	n = htonl(n);
	strcpy(out, inet_ntoa(n));
	return n;
}

int main(int argc, char *argv[])
{
	char buf[24];
	get_random_dot_ip(argv[1], argv[2], buf);
	printf("random:%s\n", buf);
}
