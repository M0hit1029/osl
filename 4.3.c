#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

FILE *fp;
pthread_mutex_t mutex;
sem_t empty, full;

void* producer(void* arg) {
    int num;
    while (1) {
        num = rand() % 10;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        fp = fopen("data.txt", "a");
        fprintf(fp, "%d\n", num);
        fclose(fp);
        printf("Produced: %d\n", num);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep((rand() % 101) * 1000);
    }
}

void* consumer(void* arg) {
    int num;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        fp = fopen("data.txt", "r");
        if (fp) {
            printf("Consumed: ");
            while (fscanf(fp, "%d", &num) != EOF)
                printf("%d ", num);
            printf("\n");
            fclose(fp);
            fp = fopen("data.txt", "w");
            fclose(fp);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(50000);
    }
}

int main() {
    pthread_t prod, cons;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}

