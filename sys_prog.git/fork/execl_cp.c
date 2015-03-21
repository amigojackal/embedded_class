#include <stdio.h>

int main()
{
	printf("pid: %d\n", getpid());
	//execl: cp -a  conf/ /tmp
	execl("/bin/cp", "cp", "-a", "conf/", "/tmp", NULL);
	printf("exec fail! %d exit\n", getpid());
}
