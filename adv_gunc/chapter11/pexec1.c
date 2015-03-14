#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * */
int main(int argc, char *argv[])
{
    printf("Running ps with execlp\n");
    execlp("/sbin/ifconfig", "ifconfig", "eth0",  0);
    perror("error");
    printf("It should not never run here\n");
    exit(0);
}
