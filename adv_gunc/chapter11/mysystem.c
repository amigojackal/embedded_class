
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/*
 * demo fork() return twice and env test varibles
 * I want to know exit value
 * */

int counter = 0;
int main(int argc, char *argv[])
{
    pid_t rev;
    int n;
    char *message;
    if (argc < 2) {
	printf("using %s <execv>\n", argv[0]);
	printf("Ex: %s ps\n", argv[0]);
	exit(0);
    }
    rev = fork();
    switch(rev) 
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        message = "This is the child";
   	execlp(argv[1], argv[1], 0);
  	perror("error");
	printf("It should not never run here\n");
	exit(0);
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
