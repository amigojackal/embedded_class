#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include <limits.h>
#include <sys/resource.h>

#define OPEN_MAX_GUESS 256

long open_max(void)
{
    long openmax;
    struct rlimit rl;

    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX) {
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
	    perror("can't get file limit");
	if (rl.rlim_max == RLIM_INFINITY)
	    openmax = OPEN_MAX_GUESS;
	else
	    openmax = rl.rlim_max;
    }
    return (openmax);
}



/*
 *  * Pointer to array allocated at run-time.
 *   */
static pid_t *childpid = NULL;

/*
 *  * From our open_max(), Figure 2.16.
 *   */
static int maxfd;

FILE *my_popen(const char *cmdstring, const char *type)
{
    int i;
    int pfd[2];
    pid_t pid;
    FILE *fp;

    /* only allow "r" or "w" */
    if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0) {
	errno = EINVAL;		/* required by POSIX */
	return (NULL);
    }

    if (childpid == NULL) {	/* first time through */
	/* allocate zeroed out array for child pids */
	maxfd = open_max();
	if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
	    return (NULL);
    }

    if (pipe(pfd) < 0)
	return (NULL);		/* errno set by pipe() */

    if ((pid = fork()) < 0) {
	return (NULL);		/* errno set by fork() */
    } else if (pid == 0) {	/* child */
	if (*type == 'r') {
	    close(pfd[0]);
	    if (pfd[1] != STDOUT_FILENO) {
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	    }
	} else {
	    close(pfd[1]);
	    if (pfd[0] != STDIN_FILENO) {
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
	    }
	}

	/* close all descriptors in childpid[] */
	for (i = 0; i < maxfd; i++)
	    if (childpid[i] > 0)
		close(i);

	execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
	_exit(127);
    }

    /* parent continues... */
    if (*type == 'r') {
	close(pfd[1]);
	if ((fp = fdopen(pfd[0], type)) == NULL)
	    return (NULL);
    } else {
	close(pfd[0]);
	if ((fp = fdopen(pfd[1], type)) == NULL)
	    return (NULL);
    }

    childpid[fileno(fp)] = pid;	/* remember child pid for this fd */
    return (fp);
}


int my_pclose(FILE * fp)
{
    int fd, stat;
    pid_t pid;

    if (childpid == NULL) {
	errno = EINVAL;
	return (-1);		/* popen() has never been called */
    }

    fd = fileno(fp);
    if ((pid = childpid[fd]) == 0) {
	errno = EINVAL;
	return (-1);		/* fp wasn't opened by popen() */
    }

    childpid[fd] = 0;
    if (fclose(fp) == EOF)
	return (-1);

    while (waitpid(pid, &stat, 0) < 0)
	if (errno != EINTR)
	    return (-1);	/* error other than EINTR from waitpid() */

    return (stat);		/* return child's termination status */
}
int main(int argc, char *argv[])
{
    FILE *fd;
    char buf[1024];

    if (argc < 2)
	goto out;
    if ((fd = my_popen(argv[1], "r")) == NULL)
	goto out;
    while (fgets(buf, sizeof(buf), fd) != NULL)
	printf("###%s", buf);
    my_pclose(fd);
out:
    return 0;
}
/*
int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
	if (isupper(c))
	    c = tolower(c);
	if (putchar(c) == EOF)
	    err_sys("output error");
	if (c == '\n')
	    fflush(stdout);
    }
    exit(0);
}
*/
