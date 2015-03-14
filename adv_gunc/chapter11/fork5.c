#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/*
 * demo fork() return twice and env test varibles
 * */

int counter = 0;
int main(int argc, char *argv[])
{
    pid_t pid;
    char *message;
    int n, offset;

    setenv("ABC", "XYZ", 1);
    printf("before fork program starting, my pid is %d, counter is %d\n", getpid(), counter ++);
    pid = fork();
    printf("after fork() %d is returned, my pid is %d, counter is %d \n", pid, getpid(), counter++);
    switch(pid) 
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        message = "This is the child";
	offset = 10;
	printf("A env ABC is %s from pid %d, offset is %d\n", getenv("ABC"), getpid(), offset);
        n = 5;
        break;
    default:
        message = "This is the parent";
	offset = 100;
	printf("A env ABC is %s from pid %d, offset is %d\n", getenv("ABC"), getpid(), offset);
        n = 3;
        break;
    }

    for(; n > 0; n--) {
        printf("%s counter is :%d\n", message, counter += offset);
        sleep(1);
    }
    exit(0);
}
