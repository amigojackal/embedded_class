#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);
int run_now = 1;
char message[] = "Hello World";
unsigned int num;
const unsigned int count = 20000000;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    int print_count1 = 0;
    int n = 0;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    for (n = 0; n < count; n++) {
		num++;
    }

    printf("\nWaiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    printf("num is :%lu\n", num);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int print_count2 = 0;
    int n;

    for (n = 0; n < count; n++) {
		num++;
    }
}
