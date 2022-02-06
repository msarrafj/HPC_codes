#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "papi.h"
#include "mkl.h"
#define NUM_EVENTS 3

#ifndef SIZE
#define SIZE  
#endif

#ifndef THREADS
#define THREADS
#endif

#define N SIZE
int main()
{
    double *A, *B, *C;
    int m, n, k, i, j;
    double alpha, beta;

    printf ("\n This example computes real matrix C=alpha*A*B+beta*C using \n"
            " Intel(R) MKL function dgemm, where A, B, and  C are matrices and \n"
            " alpha and beta are double precision scalars\n\n");

    m = SIZE, k = SIZE, n = 1;
    printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
            " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);
    alpha = 1.0; beta = 0.0;

    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    A = (double *)mkl_malloc( m*k*sizeof( double ), 64 );
    B = (double *)mkl_malloc( k*n*sizeof( double ), 64 );
    C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
      mkl_free(A);
      mkl_free(B);
      mkl_free(C);
      return 1;
    }

    printf (" Intializing matrix data \n\n");
    for (i = 0; i < (m*k); i++) {
        A[i] = (double)(i+1);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (double)(-i-1);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    	long long start_time, end_time;
  	long long values[NUM_EVENTS];
    	int eventset = PAPI_NULL;
    	PAPI_library_init(PAPI_VER_CURRENT);
    	PAPI_create_eventset(&eventset);
   	PAPI_add_event(eventset, PAPI_L1_TCM);
   	PAPI_add_event(eventset, PAPI_L2_TCM);
   	PAPI_add_event(eventset, PAPI_L3_TCM);

    	PAPI_start(eventset);
	printf("%d_threads_runned\n",THREADS);
	// run
	start_time = PAPI_get_real_usec();
    	printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
	omp_set_num_threads(THREADS);
    	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
        m, n, k, alpha, A, k, B, n, beta, C, n);
	end_time = PAPI_get_real_usec();

	PAPI_read(eventset, values);
	PAPI_stop(eventset, values);
	printf("Time = %lli\n", end_time - start_time);
	printf("L1_misses = %lli \n", values[0]);
	printf("L2_misses = %lli \n", values[1]);
	printf("L3_misses = %lli \n", values[2]);
	PAPI_reset(eventset);

    //printf ("\n Computations completed.\n\n");
    //printf ("\n Deallocating memory \n\n");
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);

    //printf (" Example completed. \n\n");
    return 0;
}
