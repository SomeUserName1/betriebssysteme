#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

sem_t aArrived, bArrived;

void *child_1(void *arg) {
    printf("child 1: before\n");

    sleep(1);
    sem_post(&aArrived);
    sem_wait(&bArrived);

    printf("child 1: after\n");
    return NULL;
}

void *child_2(void *arg) {
    printf("child 2: before\n");

    sleep(1);
    sem_post(&bArrived);
    sem_wait(&aArrived);

    printf("child 2: after\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("parent: begin\n");
    sem_init(&aArrived, 0, 0);
    sem_init(&bArrived, 0, 0);
    Pthread_create(&p1, NULL, child_1, NULL);
    Pthread_create(&p2, NULL, child_2, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("parent: end\n");
    return 0;
}
