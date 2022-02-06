#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include "papi.h"

#define NUM_EVENTS 3

#ifndef SIZE
#define SIZE  
#endif
#define MATRIX_SIZE SIZE



#ifndef THREADS
#define THREADS
#endif

#ifndef BLOCK_SIZE
#define BLOCK_SIZE
#endif


//int BLOCK_SIZE[] = {4,16,64,256,512,1024,2048};
//int THREADS[] = {4,16,28,56,112}; 

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
	int bb,th,k, j, i, jj, kk;
	
	// Initalize array A and B with '1's
	for (i = 0; i < MATRIX_SIZE; ++i) {
		for (k = 0; k < MATRIX_SIZE; ++k) {
			A[i][k] = rand() % (101);
			B[i][k] = rand() % (101);
		}
	}
	// Run for each block size
		memset(C, 0, sizeof(C[0][0] * MATRIX_SIZE * MATRIX_SIZE));
		omp_set_num_threads(THREADS);
	
		double start = omp_get_wtime();	
			// Do block matrix multiplication
	
			#pragma omp parallel for
			for (k = 0; k < MATRIX_SIZE; k += BLOCK_SIZE) {
		//		#pragma omp parallel for
				for (j = 0; j < MATRIX_SIZE; j += BLOCK_SIZE) {
		//			#pragma omp parallel for
					for (i = 0; i < MATRIX_SIZE; ++i) {
					
						for (jj = j; jj < min(j + BLOCK_SIZE, MATRIX_SIZE); ++jj){
							for (kk = k; kk < min(k + BLOCK_SIZE, MATRIX_SIZE); ++kk) {
								C[i][jj] += A[i][kk] * B[kk][jj];
							}
						}
					}
				}
			}

			// Keep track of when we finish our work
        		double end = omp_get_wtime();
        		printf("Time:%1.9f\n",end-start);
			
		
		puts("");
	
	return 0;
}

