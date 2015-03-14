#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0) {
	printf("pipe3 before pipe[0]=%d, pipe[1]=%d\n", file_pipes[0], file_pipes[1]);
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0) {
	    printf("pipe3 child pipe[0]=%d, pipe[1]=%d exec pipe4\n", file_pipes[0], file_pipes[1]);
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe4", "pipe4", buffer, (char *)0);
            exit(EXIT_FAILURE);
        }
        else {
	    printf("pipe3 parent pipe[0]=%d, pipe[1]=%d write data: %s\n", file_pipes[0], file_pipes[1], some_data);
            data_processed = write(file_pipes[1], some_data,
                                   strlen(some_data));
            printf("pipe3 parent %d - wrote %d bytes to file_pipes[0]\n", getpid(), data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}

