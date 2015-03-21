#include <sys/types.h>
#include <signal.h>

#include <stdio.h>

#include <unistd.h>
static int alarm_fired = 0;

void ding(int sig)
{
    alarm_fired = 1;
}



int main()
{
    pid_t pid;
    printf("alarm application starting\n");
    pid = fork();
    switch (pid) {

    case -1:
	/* Failure */
	perror("fork failed");
	exit(1);

    case 0:
	/* child */
	sleep(1);
	kill(getppid(), SIGALRM);
	exit(0);
    }

    printf("waiting for alarm to go off \n");
    sleep(1);
    (void) signal(SIGALRM, ding);

    pause();
    if (alarm_fired)
	printf("Ding!\n");
    printf("done\n ");
    exit(0);
}
