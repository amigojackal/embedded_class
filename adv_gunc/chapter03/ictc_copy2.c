#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int is_regular_file(const char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
		return 0;
	if (S_ISREG(st.st_mode))
		return 1;
	return 0;
}


int main(int argc, char *argv[])
{
	char block[1024];
	int in, out;
	int nread;

	if (argc < 3) {
		printf("usage: %s <src> <dst>\n", argv[0]);
		exit(0);
	}
	if (!is_regular_file(argv[1])) {
		printf("src :%s is not regular file\n", argv[1]);
		exit(0);
	}
	in = open(argv[1], O_RDONLY);
	if (in == -1) {
		printf("can not open src: %s\n", argv[1]);
		exit(0);
	}
	out = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (!is_regular_file(argv[2])) {
		printf("dst :%s is not regular file\n", argv[2]);
		exit(0);
	}
	if (out == -1) {
		printf("can not open dst: %s\n", argv[2]);
		exit(0);
	}
	while ((nread = read(in, block, sizeof(block))) > 0)
		write(out, block, nread);
	close(in);
	close(out);
	exit(0);
}
