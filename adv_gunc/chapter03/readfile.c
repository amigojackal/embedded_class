#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fd;
	char buf[1024];

	fd = fopen("/etc/hosts", "r");

	if (fd == NULL) {
		printf("Can not open file\n");
		exit (-1);
	}
	while (fgets(buf, sizeof(buf), fd))
		printf("[%s]\n", buf);
}
