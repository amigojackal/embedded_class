#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int do_tar(const char *src)
{
	char buf[1024];
	int x, rev = -1;
	
	if ((x = fork()) == -1)
		goto sys_out;
	if (x == 0) {
		sprintf(buf, "%s.tgz", src);
		printf("child to exec: tar czvf %s %s\n", buf, src);
		execlp("tar", "tar", "czvf", buf, src, 0);
		perror("exec tar error");
		exit(-1);
	} else {
		int status;

		printf("parent process pid:%d, my child pid:%d\n",
		 				getpid(), x);
		waitpid(0, &status, 0);
		if (!WIFEXITED(status)) {
			printf("child cp error\n");
			exit(1);
		}
		if (WEXITSTATUS(status) == 0) {
			printf("Nice! copy and tar ok\n");
		} else {
			printf("something error or fail in tar\n");
			goto sys_out;
		}
	}
	return 0;
sys_out:
	perror("sys error");
	return rev;
}
int main(int argc, char *argv[])
{
	int x;

	if (argc < 3) {
		printf("usage: %s <src> <dst>\n"
			"\t eg: %s /tmp/xxx /tmp/yyy\n",
			argv[0], argv[0]);
		exit(1);
	}
	x = fork();

	if (x == -1) {
		printf("fork error\n");
		exit(-1);
	} else if (x == 0) {
		printf("child process pid:%d exec:cp -a %s %s\n",
			getpid(), argv[1], argv[2]);
		execlp("cp", "cp", "-a", argv[1], argv[2], (char *)NULL);
		perror("exec fail");
		exit(1);
	} else {
		int status;

		printf("parent process pid:%d, my child pid:%d\n",
		 				getpid(), x);
		waitpid(0, &status, 0);
		if (!WIFEXITED(status)) {
			printf("child cp error\n");
			exit(1);
		}
		if (WEXITSTATUS(status) == 0) {
			if (do_tar(argv[2]) != 0) 
				printf("tar %s fail\n", argv[2]);
		}
	}
	printf("pid :%d exiting\n", getpid());
	exit(0);
}
