#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXLINE 4096
int main(void)
{
    int n;
    int fd[2];
    pid_t pid;
    char line[4096];

    if (pipe(fd) < 0)
	perror("pipe error");
    if ((pid = fork()) < 0) {
	perror("fork error");
    } else if (pid > 0) {	/* parent */
	close(fd[0]);
	write(fd[1], "hello world\n", 12);
    } else {			/* child */
	close(fd[1]);
	n = read(fd[0], line, MAXLINE);
	write(STDOUT_FILENO, line, n);
    }
    exit(0);
}
