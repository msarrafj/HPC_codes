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
#define N SIZE



#ifndef THREADS
#define THREADS
#endif

#ifndef BLOCK_SIZE
#define BLOCK_SIZE
#endif


//int BLOCK_SIZE[] = {4,16,64,256,512,1024,2048};
//int THREADS[] = {4,16,28,56,112}; 


double A[N][N];
double B[N][N];
double C[N][N];


void init_array()
{
	int i,k;
	
	for (i = 0; i < N; ++i) {
		for (k = 0; k < N; ++k) {
			A[i][k] = rand() % (101);
			B[i][k] = rand() % (101);
			C[i][k] = rand() % (101);
		}
	}
}

void serial()
{
	int i, j, k, jj, kk;
	
//	#pragma omp parallel for
	for (k = 0; k < N; k += BLOCK_SIZE) {
//		#pragma omp parallel for
		for (j = 0; j < N; j += BLOCK_SIZE) {
//			#pragma omp parallel for
			for (i = 0; i < N; ++i) {
			
				for (jj = j; jj < min(j + BLOCK_SIZE, N); ++jj){
					for (kk = k; kk < min(k + BLOCK_SIZE, N); ++kk) {
						C[i][jj] += A[i][kk] * B[kk][jj];
					}
				}
			}
		}
	}
}


void outer_paral()
{
	int i, j, k, jj, kk;
	
	#pragma omp parallel for
	for (k = 0; k < N; k += BLOCK_SIZE) {
//		#pragma omp parallel for
		for (j = 0; j < N; j += BLOCK_SIZE) {
//			#pragma omp parallel for
			for (i = 0; i < N; ++i) {
			
				for (jj = j; jj < min(j + BLOCK_SIZE, N); ++jj){
					for (kk = k; kk < min(k + BLOCK_SIZE, N); ++kk) {
						C[i][jj] += A[i][kk] * B[kk][jj];
					}
				}
			}
		}
	}
}

void middle_paral()
{
	int i, j, k, jj, kk;
	
//	#pragma omp parallel for
	for (k = 0; k < N; k += BLOCK_SIZE) {
		#pragma omp parallel for
		for (j = 0; j < N; j += BLOCK_SIZE) {
//			#pragma omp parallel for
			for (i = 0; i < N; ++i) {
			
				for (jj = j; jj < min(j + BLOCK_SIZE, N); ++jj){
					for (kk = k; kk < min(k + BLOCK_SIZE, N); ++kk) {
						C[i][jj] += A[i][kk] * B[kk][jj];
					}
				}
			}
		}
	}
}

void inner_paral()
{
	int i, j, k, jj, kk;
	
//	#pragma omp parallel for
	for (k = 0; k < N; k += BLOCK_SIZE) {
//		#pragma omp parallel for
		for (j = 0; j < N; j += BLOCK_SIZE) {
			#pragma omp parallel for
			for (i = 0; i < N; ++i) {
			
				for (jj = j; jj < min(j + BLOCK_SIZE, N); ++jj){
					for (kk = k; kk < min(k + BLOCK_SIZE, N); ++kk) {
						C[i][jj] += A[i][kk] * B[kk][jj];
					}
				}
			}
		}
	}
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int main(int argc, char*  argv[])
{
        int i,j;
	long long start_time, end_time;
	long long values[NUM_EVENTS];
	int eventset = PAPI_NULL;
	PAPI_library_init(PAPI_VER_CURRENT);
	PAPI_create_eventset(&eventset);
	PAPI_add_event(eventset, PAPI_L1_TCM);
	PAPI_add_event(eventset, PAPI_L2_TCM);
	PAPI_add_event(eventset, PAPI_L3_TCM);
	// Initalize our matix looping variables once
	init_array();
	printf("BLOCK:%d\n", BLOCK_SIZE);
		
	//memset(C, 0, sizeof(C[0][0] * N * N));
	PAPI_start(eventset);
	printf("Threads:%d\n",THREADS);
	omp_set_num_threads(THREADS);
	
	// run
	start_time = PAPI_get_real_usec();
        if (strcmp (argv[1], "serial") == 0){
		printf("SERIAL CASE IS RUNNING\n");
		serial();
	}
        else if (strcmp (argv[1], "outerParal") == 0){
		printf("OUTER PARAL CASE IS RUNNING\n");
		outer_paral();
	}
        else if (strcmp (argv[1], "middleParal") == 0){
		printf("MIDDLE PARAL CASE IS RUNNING\n");
		middle_paral();
	}
        else if (strcmp (argv[1], "innerParal") == 0){
		printf("INNER PARAL CASE IS RUNNING\n");
		inner_paral();
	}
	else{
	printf("WRONG FUNCTION INSERTED \n");
	}

	end_time = PAPI_get_real_usec();

	PAPI_read(eventset, values);
	PAPI_stop(eventset, values);
	printf("Time = %lli\n", end_time - start_time);
	printf("L1_misses = %lli \n", values[0]);
	printf("L2_misses = %lli \n", values[1]);
	printf("L3_misses = %lli \n", values[2]);
	PAPI_reset(eventset);

		
return 0;
}

