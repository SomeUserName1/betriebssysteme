#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"

typedef struct __barrier_t {
    int   number_of_threads;
    int   count_threads;
    sem_t lock;
    sem_t allArrived;
} barrier_t;

barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
    b->number_of_threads = num_threads;
    b->count_threads = 0;
    sem_init(&b->lock, 0, 1);
    sem_init(&b->allArrived, 0, 0);
}

void barrier(barrier_t *b) {
    sem_wait(&b->lock);
    b->count_threads++;
    sem_post(&b->lock);

    if(b->count_threads == b->number_of_threads) {
      sleep(1);
      sem_post(&b->allArrived);
    }

    sem_wait(&b->allArrived);
    sleep(1);
    sem_post(&b->allArrived);
}


typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}


int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);

    int i;
    for (i = 0; i < num_threads; i++) {
	    t[i].thread_id = i;
	    Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++)
	    Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}
