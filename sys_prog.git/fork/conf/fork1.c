#include <stdio.h>

int main()
{
	int pid;
	printf("hello my pid is :%d\n", getpid());
	
	pid = fork();
	printf("hi my pid is: %d, the fork() return: %d\n", getpid(), pid);
}
