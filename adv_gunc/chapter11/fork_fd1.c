#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int x;
	int fd;
	int ch;
	int max = 5;

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror("open error");
		return -1;
	}

	x = fork();
	if (x == -1)
		return -1;
	if (x == 0) {
		while (read(fd, &ch, 1)) {
			printf("child read:[%c]\n", ch);
			sleep(1);
		}
	} else {
		while (read(fd, &ch, 1)) {
			printf("parent read:[%c]\n", ch);
			sleep(1);
		}

	}
	return 0;
}
