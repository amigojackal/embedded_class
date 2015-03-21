#include <stdio.h>

int main()
{
	int ret, status;

	ret = fork();

	if (ret == 0) { //child
		printf("pid: %d\n", getpid());
		//execl: cp -a  conf/ /tmp
		execl("/bin/cp", "cp", "-a", "conf/", "/tmp", NULL);
		printf("exec fail! %d exit\n", getpid());
		exit(-1);
	} else { // pararnt
		printf("this is parart: ret: %d\n", ret);
		waitpid(ret, &status, 0);
		printf("child pid: %d already finish\n", ret);
	}
}
