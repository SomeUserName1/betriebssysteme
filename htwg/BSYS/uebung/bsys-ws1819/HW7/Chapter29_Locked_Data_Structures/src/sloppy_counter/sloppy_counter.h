#ifndef CONCURRENT_COUNTER_H_
#define CONCURRENT_COUNTER_H_

#include <assert.h>
#include <pthread.h>
#include <sys/sysinfo.h>

typedef struct __counter_t {
  int             global_count;
  pthread_mutex_t global_lock;
  int             local_count[NUMBER_OF_CPUS];
  pthread_mutex_t local_lock[NUMBER_OF_CPUS];
  int             threshold;
} counter_t;

/* The function 'init' initializes the counter:
     initialize threshold,
     initialize locks (global and local),
     initialize count (global and local). */
void init(counter_t *counter, int threshold) {
  counter->threshold = threshold;
  counter->global_count = 0;
  int glrc = pthread_mutex_init(&counter->global_lock, NULL);
  assert(glrc == 0);
  for (int i = 0; i < NUMBER_OF_CPUS; i++) {
    counter->local_count[i] = 0;
    int llrc = pthread_mutex_init(&counter->local_lock[i], NULL);
    assert(llrc == 0);
  }
}

/* The function 'update' updates the counter:
     grabs first the local lock and updates the local_count by amount.
     Once the local_lock has risen by 'threshold', grab the
     global_lock and transfer the local_count value to it. */
void update(counter_t *counter, long int tid, int amount) {
  int cpu_number = tid % NUMBER_OF_CPUS;
  pthread_mutex_lock(&counter->local_lock[cpu_number]);

  counter->local_count[cpu_number] += amount;

  // transfer local_count to global_count
  if (counter->local_count[cpu_number] >= counter->threshold) {
    pthread_mutex_lock(&counter->global_lock);
    counter->global_count += counter->local_count[cpu_number];
    pthread_mutex_unlock(&counter->global_lock);
    counter->local_count[cpu_number] = 0;
  }

  pthread_mutex_unlock(&counter->local_lock[cpu_number]);
}

/* The function 'get_global_counter_value' returns the value of the
   global counter. */
int get_global_count_value(counter_t *counter) {
  pthread_mutex_lock(&counter->global_lock);
  int global_count_value = counter->global_count;
  pthread_mutex_unlock(&counter->global_lock);
  return global_count_value;
}

#endif
