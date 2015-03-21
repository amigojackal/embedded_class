#include <stdio.h>

int main()
{
	FILE *fp;
	char buf[1024];

	//fp = popen("ifconfig eth0", "r");
	fp = popen("ifconfig  eth0|grep Mask|cut -d : -f 2|cut -d ' ' -f 1", "r");
	while (fgets(buf, 1024, fp) != NULL) {
		printf("buf: %s", buf);
	}
	
}
