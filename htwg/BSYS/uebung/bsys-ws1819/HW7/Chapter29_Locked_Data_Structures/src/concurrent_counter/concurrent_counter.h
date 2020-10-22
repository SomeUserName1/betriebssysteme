#ifndef CONCURRENT_COUNTER_H_
#define CONCURRENT_COUNTER_H_

#include <assert.h>
#include <pthread.h>

typedef struct __counter_t {
  int             value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *counter) {
  counter->value = 0;
  int rc = pthread_mutex_init(&counter->lock, NULL);
  assert(rc == 0);
}

void increment(counter_t *counter) {
  pthread_mutex_lock(&counter->lock);
  counter->value++;
  pthread_mutex_unlock(&counter->lock);
}

void decrement(counter_t *counter) {
  pthread_mutex_lock(&counter->lock);
  counter->value--;
  pthread_mutex_unlock(&counter->lock);
}

int get_value(counter_t *counter) {
  pthread_mutex_lock(&counter->lock);
  int counter_value = counter->value;
  pthread_mutex_unlock(&counter->lock);
  return counter_value;
}

#endif
