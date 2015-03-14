#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
	printf("using %s <exec>\nEx: %s ps\n", argv[0], argv[0]);
	exit(0);
    }
    printf("Running ps with execlp\n");
    execlp(argv[1], argv[1], 0);
    perror("error");
    printf("It should not never run here\n");
    exit(0);
}
