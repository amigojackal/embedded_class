// The 'consumer' program, pipe4.c, that reads the data is much simpler.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int data_processed;
    char buffer[BUFSIZ + 1];
    int file_descriptor;

    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_descriptor);
    printf("pipe4: argv[1] = %s, get pipe descrip[0] is :%d\n", argv[1], file_descriptor);
    data_processed = read(file_descriptor, buffer, BUFSIZ);

    printf("pipe4: %d - read %d bytes: %s from pipe[0]: %d\n", getpid(), data_processed, buffer, file_descriptor);
    exit(EXIT_SUCCESS);
}
