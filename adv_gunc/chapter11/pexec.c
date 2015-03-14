#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Running ps with execlp\n");
    execlp("sleep", "xxxxxxxxxx","10", 0);
    printf("Done.\n");
    exit(0);
}
