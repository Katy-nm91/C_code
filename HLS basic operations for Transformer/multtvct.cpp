
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "multtvct.hpp"
//#include "test_lib.hpp"

// This module performs matrix multiplication of matrices A and B
// Where A is an (m,n) and B is an (n,o) matrix.
// We assume that B is stored transposed, resulting in a (o,n) shape. --
void multtvct(
		int a_buff[M][N], int b_buff[N], int c_buff[M]
  ) {

//		  volatile int *a,
//		  volatile int *b,
//		  volatile int *c) {
//		#pragma HLS INTERFACE m_axi port = a offset = slave bundle = a_port
//		#pragma HLS INTERFACE m_axi port = b offset = slave bundle = b_port
//		#pragma HLS INTERFACE m_axi port = c offset = slave bundle = c_port
//		#pragma HLS INTERFACE s_axilite port = return bundle = CONTROL_BUS
//
//		  int a_buff[M][N];
//		  int b_buff[N];
//		  int c_buff[M];
//		  // Load A & B
//		  memcpy(&a_buff[0][0], const_cast<int*>(a), sizeof(int) * M * N);
//		  memcpy(&b_buff[0], const_cast<int*>(b), sizeof(int) * N);


	LOOP1: for (int m=0; m<M; m++) {
	      c_buff [m] = 0;
       // #pragma HLS pipeline II = 1
		LOOP2: for (int n=0; n<N; n++) {
        //    #pragma HLS unroll
			c_buff[m] += a_buff[m][n] * b_buff[n];

		}
	}

	  // Store C
	  // memcpy(const_cast<int*>(c), const_cast<int*>(&c_buff[0]), sizeof(int) * M);

}
