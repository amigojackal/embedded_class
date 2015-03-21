#include <stdio.h>

int main()
{
	printf("pid: %d\n", getpid());
	//execl: cp -a  conf/ /tmp
	execl("/bin/cp", "cp", "-a", "conf/", "/tmp", NULL);
	printf("pid: %d exit\n", getpid());
}
