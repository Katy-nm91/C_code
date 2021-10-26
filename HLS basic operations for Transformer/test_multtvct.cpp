#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "multtvct.hpp"
//#include "test_lib.hpp"

void * allocBuffer(size_t num_bytes) {
#ifdef NO_SIM
  return cma_alloc(num_bytes, CACHED);
#else
  return malloc(num_bytes);
#endif
}

void freeBuffer(void * buffer) {
#ifdef NO_SIM
  return cma_free(buffer);
#else
  return free(buffer);
#endif
}

int main(void) {

  // Test outcome
  bool correct = true;

  // Reference output
  int c_ref[M];

  // Input and output array initialization
//  int *a = (int *) allocBuffer(sizeof(int) * M * N);
//  int *b = (int *) allocBuffer(sizeof(int) *N);
//  int *c = (int *) allocBuffer(sizeof(int) * M);
  int a[M][N];
  int b[N];
  int c[M];

  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      a[m][n] = 5;
    }
  }

  for (int n = 0; n < N; n++) {
    b[n] = 2;
  }

  for (int m = 0; m < M; m++) {
    c[m] = 0;
    c_ref[m] = 0;
  }

  // Invoke the matrix multiply module
#if NO_SIM
  uint64_t t_fpga = multtvct(a, b, c);
  printf("Synchronization time: %.3lfms\n", static_cast<float>(t_fpga) / 1E6);
#else
  multtvct(a, b, c);
#endif

  // Check output
  for (int m = 0; m < M; m++) {
      for (int n = 0; n < N; n++) {
        c_ref[m] += a[m][n] * b[n];
      }
      if (c_ref[m] != c[m]) {
        correct = false;
      }
  }


  if (correct) {
    printf("Test successful\n");
    return 0;
  } else {
    printf("Test unsuccessful\n");
    return -1;
  }
}
