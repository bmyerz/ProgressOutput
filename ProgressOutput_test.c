#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "ProgressOutput.h"

#define BILLION 1000000000

#define FLUSH_INTERVAL  (1<<25)

const int64_t size = 2;
ProgressOutput count1_po;
ProgressOutput count2_po;

int main() {
  ProgressOutput_init( 1, 2, PO_ARG(count1_po), PO_ARG(count2_po) );

  uint64_t count1 = 0;
  uint64_t count2 = 0;
  for (uint64_t i=0; i<BILLION; i++) {
    count1+=1;
    count2+=2;
    if ( i % FLUSH_INTERVAL == 0 ) {
      ProgressOutput_updateShared( &count1_po, count1 );
      ProgressOutput_updateShared( &count2_po, count2 );
    }
  }
}
