#include <stdio.h>
#include <signal.h>

int X;

void sig_xxx(int sig)
{
	printf("ALARM\n");
	X = sum(X, 2);
	signal(SIGALRM, SIG_DFL);
}

int sum(int x, int y)
{
	sleep(1);
	return x + y;
}

int main(int argc, char *argv[])
{
	unsigned int i = 1;

	signal(SIGALRM, sig_xxx);
	for (i = 0;i < 10 ;i++){
		alarm(1);
		X = sum(X, 1);
	}
	printf("TOTAL SUM:%d\n", X);	
}
