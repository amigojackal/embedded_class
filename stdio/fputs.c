#include <stdio.h>

int main(int argc, char *argv[])
{
	char buf[1024];

	while (fgets(buf, sizeof(buf), stdin)) {
		printf("+++++++\n");
		fputs(buf, stdout);
		printf("#######\n");
	}
	return(0);
}
