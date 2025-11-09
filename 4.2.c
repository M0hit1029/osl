#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_STUDENTS 5
#define NUM_CHAIRS 3

sem_t students;
sem_t ta;
pthread_mutex_t mutex;
int waiting = 0;

void* ta_thread(void* arg) {
    while (1) {
        sem_wait(&students);
        pthread_mutex_lock(&mutex);
        waiting--;
        printf("TA is helping a student. Waiting students: %d\n", waiting);
        pthread_mutex_unlock(&mutex);
        sem_post(&ta);
        sleep(2);
        printf("TA finished helping a student.\n");
    }
}

void* student_thread(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        if (waiting < NUM_CHAIRS) {
            waiting++;
            printf("Student %d is waiting. Waiting students: %d\n", id, waiting);
            pthread_mutex_unlock(&mutex);
            sem_post(&students);
            sem_wait(&ta);
            printf("Student %d is getting help from TA.\n", id);
        } else {
            pthread_mutex_unlock(&mutex);
            printf("Student %d found no empty chair. Will come back later.\n", id);
        }
        sleep(rand() % 5 + 1);
    }
}

int main() {
    pthread_t ta_tid, student_tid[NUM_STUDENTS];
    int id[NUM_STUDENTS];
    sem_init(&students, 0, 0);
    sem_init(&ta, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&ta_tid, NULL, ta_thread, NULL);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        id[i] = i + 1;
        pthread_create(&student_tid[i], NULL, student_thread, &id[i]);
    }
    pthread_join(ta_tid, NULL);
    for (int i = 0; i < NUM_STUDENTS; i++)
        pthread_join(student_tid[i], NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&students);
    sem_destroy(&ta);
    return 0;
}

