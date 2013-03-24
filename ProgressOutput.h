#pragma once

#include <stdint.h>

typedef struct ProgressOutput {
  uint64_t shared_val; 

  pthread_mutex_t m;
} ProgressOutput;

void ProgressOutput_updateShared( ProgressOutput * o, uint64_t val );

void ProgressOutput_init( uint64_t interval_sec, uint64_t num, ...);

#define PO_ARG(var) &var,#var
