#include <stdio.h>
#include <pthread.h>

int contador = 0;
pthread_mutex_t lock;

void *incrementa_contador(void *arg) {
    pthread_mutex_lock(&lock);
    contador++;
    printf("Contador = %d\n", contador);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[10];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, incrementa_contador, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
