#include <stdio.h>


int main(int argc, char *argv[])
{
	int x;
	printf("###%s.%d: hi ictc pid:%d\n",
		 __FUNCTION__, __LINE__, getpid());
	x = fork();

	printf("###%s.%d: hi ictc pid:%d x=%d\n",
		 __FUNCTION__, __LINE__, getpid(), x);
}
