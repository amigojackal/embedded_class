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
static void sig_reconfig(int signo)
{
	printf("\n	%s:%d> get sig(%d) to reconfig\n", __FUNCTION__, __LINE__, signo);
	return;
}

int main()
{
	signal(SIGINT, my_int);
	signal(SIGABRT, my_int);
	signal(SIGHUP, sig_reconfig);
	signal(SIGUSR1, sig_reconfig);
	signal(SIGUSR2, sig_reconfig);
	printf("%s:%d> is waitting sig\n", __FUNCTION__, __LINE__);
	pause();
	printf("%s:%d> is waitting sig\n", __FUNCTION__, __LINE__);
}
