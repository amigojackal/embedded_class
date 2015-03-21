#include <stdio.h>

int main()
{
	printf("pid: %d\n", getpid());
	execl("/bin/ls", "ls", "-l", NULL);
	printf("pid: %d exit\n", getpid());
}
