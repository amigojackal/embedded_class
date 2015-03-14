#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/*
 * demo fork() return twice
 * */
int main(int argc, char *argv[])
{
    pid_t pid;
    char *message;
    int n;

    printf("before fork program starting, my pid is %d\n", getpid());
    pid = fork();
    printf("after fork() %d is returned, my pid is %d \n", pid, getpid());
    switch(pid) 
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        message = "This is the child";
        n = 5;
        break;
    default:
        message = "This is the parent";
        n = 3;
        break;
    }

    for(; n > 0; n--) {
        puts(message);
        sleep(1);
    }
    exit(0);
}
