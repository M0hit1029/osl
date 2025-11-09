#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;
int readcount = 0, data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d reads flight data: %d\n", id, data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&wrt);
        data++;
        printf("Writer %d updates flight data to: %d\n", id, data);
        sem_post(&wrt);
        sleep(2);
    }
}

int main() {
    pthread_t r[3], w[2];
    int i, id[5];
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 3; i++) {
        id[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &id[i]);
    }
    for (i = 0; i < 2; i++) {
        id[i + 3] = i + 1;
        pthread_create(&w[i], NULL, writer, &id[i + 3]);
    }
    for (i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (i = 0; i < 2; i++)
        pthread_join(w[i], NULL);
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);
    return 0;
}

