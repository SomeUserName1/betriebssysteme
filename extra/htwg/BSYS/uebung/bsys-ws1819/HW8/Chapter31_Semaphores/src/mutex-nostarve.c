#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

typedef struct __ns_mutex_t {
  sem_t lock;
  sem_t turnstile1;
  sem_t turnstile2;
  int   num_threads_in_w_room_1;
  int   num_threads_in_w_room_2;
} ns_mutex_t;


void ns_mutex_init(ns_mutex_t *m) {
  sem_init(&m->lock, 0, 1);
  sem_init(&m->turnstile1, 0, 1);
  sem_init(&m->turnstile2, 0, 0);
  m->num_threads_in_w_room_1 = 0;
  m->num_threads_in_w_room_2 = 0;
}

void ns_mutex_acquire(ns_mutex_t *m) {
  sem_wait(&m->lock);
  m->num_threads_in_w_room_1++;
  sem_post(&m->lock);

  sem_wait(&m->turnstile1);
  m->num_threads_in_w_room_2++;
  sem_wait(&m->lock);
  m->num_threads_in_w_room_1--;

  if (m->num_threads_in_w_room_1 == 0) {
    sem_post(&m->lock);
    sem_post(&m->turnstile2);
  } else {
    sem_post(&m->lock);
    sem_post(&m->turnstile1);
  }

  sem_wait(&m->turnstile2);
  m->num_threads_in_w_room_2--;

}

void ns_mutex_release(ns_mutex_t *m) {
  if (m->num_threads_in_w_room_2 == 0) {
    sem_post(&m->turnstile1);
  } else {
    sem_post(&m->turnstile2);
  }
}

ns_mutex_t m;
int counter;

void *worker(void *arg) {
    ns_mutex_acquire(&m);
    counter++;
    ns_mutex_release(&m);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 3);

    const int NUM_THREADS = atoi(argv[1]);
    int loops = atoi(argv[2]);

    pthread_t threads[NUM_THREADS];

    ns_mutex_init(&m);

    printf("parent: begin\n");

    while (loops > 0) {
      for (int i = 0; i < NUM_THREADS; i++) {
        Pthread_create(&threads[i], NULL, worker, NULL);
      }

      for (int i = 0; i < NUM_THREADS; i++) {
        Pthread_join(threads[i], NULL);
      }

      loops--;
    }
    printf("counter: %d\n", counter);
    printf("parent: end\n");
    return 0;
}
