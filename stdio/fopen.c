#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fd;
	char buf[1024];

	fd = fopen(argv[1], "r");

	if (fd == NULL) {
		printf("Can not open file\n");
		return (-1);
	}
	while (fgets(buf, sizeof(buf), fd))
		printf("[%s]\n", buf);
	
	fclose(fd);
	return(0);
}
