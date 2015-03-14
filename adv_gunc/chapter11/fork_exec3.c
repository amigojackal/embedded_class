/*
 * demeo fork, execv, wait();
 * and zombie child process.
 * use: 
 * #./fork_exec3 &
 * # ps auxw
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv)
{
	int x;

	x = fork();

	if (x == -1) {
		printf("fork error\n");
		exit(-1);
	} else if (x == 0) {
		printf("child process pid:%d\n", getpid());
		execlp("./show_args", "xxx", "yyy", "zzz", (char *)NULL);
		perror("exec fail");
		exit(1);
	} else {
		int st, i;
		printf("parent process pid:%d, my child pid:%d\n",
		 getpid(), x);
		sleep(30);
		i = waitpid(0, &st, 0);
		printf("get i:%d, stauts:%d\n", i, st);
	}
	printf("pid :%d exiting\n", getpid());
	exit(0);
}
