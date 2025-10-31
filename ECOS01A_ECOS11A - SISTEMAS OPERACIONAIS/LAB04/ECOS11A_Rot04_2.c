#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int *id = (int *)arg;
    printf("Thread número %d está executando...\n", *id);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_args[5];

    for (int i = 0; i < 5; i++) {
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_args[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
