#include <stdio.h>

int main()
{
	int ret;
	printf("parant: %d\n", getpid());
	
	ret = fork();

	if (ret == 0)	//child
		printf("child pid: %d, ret: %d\n", getpid(), ret);
	else
		printf("parant pid: %d, ret: %d\n", getpid(), ret);
}
