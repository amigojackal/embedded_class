#include <stdio.h>
#include <signal.h>
#include <pwd.h>
/*
 *
 * TRY: 
 * #strace a.out
 * */
static void my_alarm(int signo)
{
    struct passwd *rootptr;

    signal(SIGALRM, my_alarm);
    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
	printf("getpwnam(root) error");
    printf("re alarm\n");
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for (;;) {
	if ((ptr = getpwnam("peter")) == NULL)
	    perror("getpwnam error");
	if (strcmp(ptr->pw_name, "peter") != 0)
	    printf("return value corrupted!, pw_name = %s\n",
		   ptr->pw_name);
    }
}
