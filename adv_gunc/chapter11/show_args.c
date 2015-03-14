#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int x;

	for (x = 0; x < argc; x ++)
		printf("argv[%d]: \"%s\"\n", x, argv[x]);

	exit(0);
}
