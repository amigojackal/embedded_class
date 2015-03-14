#include <stdio.h>


int main(int argc, char *argv[])
{
	int x;
	int z = 0, i;
	printf("###%s.%d: hi ictc pid:%d\n",
		 __FUNCTION__, __LINE__, getpid());
	x = fork();

	printf("###%s.%d: hi ictc pid:%d x=%d\n",
		 __FUNCTION__, __LINE__, getpid(), x);

	if (x == 0)
		z = 1;
	if (x > 0)
		z = 0;
	for (i = 0; i < 3; i++) {
		printf("###%s.%d: hi ictc pid:%d x=%d z=%d\n",
			 __FUNCTION__, __LINE__, getpid(), x, z);
		z = z + 2;
	}
}
