#include <stdio.h>
#include <signal.h>
#include <pwd.h>
/*
 * */
static void my_int(int signo)
{
	printf("\n	%s:%d> get %d\n", __FUNCTION__, __LINE__, signo);
	return;
}

int main()
{
	signal(SIGINT, my_int);
	signal(SIGABRT, my_int);
	printf("%s:%d> is waitting sig\n", __FUNCTION__, __LINE__);
	pause();
	printf("%s:%d> is waitting sig\n", __FUNCTION__, __LINE__);
}
