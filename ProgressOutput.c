
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdarg.h>

#include "ProgressOutput.h"

// ProgressOutput structures
uint64_t signal_interval;
pthread_t signaled_thread;

// ProgressOutput config; set during init
ProgressOutput ** registered_ptrs;
char ** registered_names;
uint64_t num_registered_ptrs;

void ProgressOutput_updateShared( ProgressOutput * o, uint64_t val ) {
  pthread_mutex_lock(&o->m);
  o->shared_val = val;
  pthread_mutex_unlock(&o->m);
}

void * signaled_thread_func( void * ignore ) {
  uint64_t counts[num_registered_ptrs];
  for (int i=0; i< num_registered_ptrs; i++) {
    pthread_mutex_lock(&registered_ptrs[i]->m);
    counts[i] = registered_ptrs[i]->shared_val;
    pthread_mutex_unlock(&registered_ptrs[i]->m);
  }

  for (int i=0; i< num_registered_ptrs; i++) {
    fprintf(stderr, "%s=%lu\n", registered_names[i], counts[i]);
  }
  alarm(signal_interval);
}

void output_handler(int sig) {
  pthread_create(&signaled_thread, NULL, &signaled_thread_func, NULL);
}


void ProgressOutput_init( uint64_t interval_sec, uint64_t num, ...) {

  num_registered_ptrs = num;
  registered_ptrs = (ProgressOutput**)malloc(num * sizeof(ProgressOutput*));
  registered_names = (char**)malloc(num * sizeof(char**));
  signal_interval = interval_sec;

  va_list vl;
  va_start(vl, num);
  for (int i=0; i<num; i++) {
    // first arg is a pointer to a ProgressOutput
    registered_ptrs[i] = va_arg(vl, ProgressOutput*);

    // second arg is a pointer to the name
    registered_names[i] = va_arg(vl, char*);

    registered_ptrs[i]->shared_val = 0;
    pthread_mutex_init(&registered_ptrs[i]->m, NULL);
  }
  va_end(vl);

  signal(SIGALRM, output_handler);
  alarm(signal_interval);
}
