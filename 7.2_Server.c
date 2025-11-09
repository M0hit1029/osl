#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, NULL, 0);
    printf("Enter message: ");
    fgets(str, 1024, stdin);
    str[strcspn(str, "\n")] = 0;
    printf("Message written to shared memory.\n");
    sleep(5);
    shmdt(str);
    return 0;
}

