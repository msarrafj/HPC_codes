#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include "papi.h"
#define NUM_EVENTS 11


double A[MATRIX_SIZE][MATRIX_SIZE],
B[MATRIX_SIZE][MATRIX_SIZE],
C[MATRIX_SIZE][MATRIX_SIZE];

int min(int a, int b)
{
	return a < b ? a : b;
}

int main(int argc, char*  argv[])
{
	// Initalize our matix looping variables once
	int k, j, i, jj, kk, bb, th, block_idx = 7, thread_idx = 5;
        long long values[NUM_EVENTS];
        int eventset = PAPI_NULL;
        PAPI_library_init(PAPI_VER_CURRENT);
        PAPI_create_eventset(&eventset);
	PAPI_add_event(eventset, PAPI_L1_TCM);
	PAPI_add_event(eventset, PAPI_L2_TCM);
	PAPI_add_event(eventset, PAPI_L3_TCM);
	
	// Initalize array A and B with '1's
	for (i = 0; i < MATRIX_SIZE; ++i) {
		for (k = 0; k < MATRIX_SIZE; ++k) {
			A[i][k] = rand() % (101);
			B[i][k] = rand() % (101);
		}
	}
	// Run for each block size
//	for (bb = 0; bb < block_idx; ++bb)
//	{
//	printf("BLOCK = %d\n", BLOCK);
		
	// Iterate through different number of threads
		
//	for (th=0; th < thread_idx; th++)
//	{
	memset(C, 0, sizeof(C[0][0] * MATRIX_SIZE * MATRIX_SIZE));
	printf("Threads = %d\n",NUMTHREADS);

	omp_set_num_threads(NUMTHREADS);
	PAPI_start(eventset);
		
	double start = omp_get_wtime();	
	// Do block matrix multiplication
	
	#pragma omp parallel for
	for (k = 0; k < MATRIX_SIZE; k += BLOCK) 
//	#pragma omp parallel for
	 for (j = 0; j < MATRIX_SIZE; j += BLOCK) {
//	  #pragma omp parallel for
	  for (i = 0; i < MATRIX_SIZE; ++i) {
           for (jj = j; jj < min(j + BLOCK, MATRIX_SIZE); ++jj){
	    for (kk = k; kk < min(k + BLOCK, MATRIX_SIZE); ++kk) {
	     C[i][jj] += A[i][kk] * B[kk][jj];
	    }
	   }
	  }
	 }
	// Keep track of when we finish our work
       	double end = omp_get_wtime();
	PAPI_read(eventset, values);
       	PAPI_stop(eventset, values);
	printf("Results_Start\n");	 
	printf("L1_Total_Cache_Misses = %lli\n",values[0]);
	printf("L2_Total_Cache_Misses = %lli\n",values[1]);
	printf("L3_Total_Cache_Misses = %lli\n",values[2]);
	printf("Time = %1.9f\n",end-start);
	printf("Results_End\n");
	PAPI_reset(eventset);	
	puts("");
	//}
	//}
return 0;
}

