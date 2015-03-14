#include <stdio.h>
/*
 * gcc fputs_stderr.c -o fputs_stderr
 *
 * fputs_stderr 2>out
 */
int main(int argc, char *argv[])
{
	char buf[1024];

	while (fgets(buf, sizeof(buf), stdin)) {
		fputs("+++++++\n", stderr);
		fputs(buf, stderr);
		fputs("#######\n", stderr);
	}
	fclose(stdout);
	return(0);
}
