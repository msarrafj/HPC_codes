#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include "papi.h"
#define NUM_EVENTS 1
#ifndef SIZE
#    define SIZE
#endif
#ifndef FLAG
#   define FLAG  
#endif

int main()
{
    double *A, *B, *C;
    int m, n, k, i, j;
    double alpha, beta;
  float MR_L1 = 0.0f;
  long long start_time, end_time;
  long long values[NUM_EVENTS];
  int eventset = PAPI_NULL;
  PAPI_library_init(PAPI_VER_CURRENT);
  PAPI_create_eventset(&eventset);
  PAPI_add_event(eventset, FLAG);
  printf("LoopType = mklMul \n");


    m = SIZE, k = SIZE, n = SIZE;
    printf("%i,%i,%i",m,k,n);
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

    printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
    PAPI_start(eventset);
    start_time = PAPI_get_real_usec();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, A, k, B, n, beta, C, n);
    printf ("\n Computations completed.\n\n");
    end_time = PAPI_get_real_usec();
    PAPI_read(eventset, values);
    PAPI_stop(eventset, values);
    printf("mklMul_time = %lli\n", end_time - start_time);
    printf("mklMul = %lli\n", values[0]);

   /* printf (" Top left corner of matrix A: \n");
    for (i=0; i<min(m,6); i++) {
      for (j=0; j<min(k,6); j++) {
        printf ("%12.0f", A[j+i*k]);
      }
      printf ("\n");
    }

    printf ("\n Top left corner of matrix B: \n");
    for (i=0; i<min(k,6); i++) {
      for (j=0; j<min(n,6); j++) {
        printf ("%12.0f", B[j+i*n]);
      }
      printf ("\n");
    }
    
    printf ("\n Top left corner of matrix C: \n");
    for (i=0; i<min(m,6); i++) {
      for (j=0; j<min(n,6); j++) {
        printf ("%12.5G", C[j+i*n]);
      }
      printf ("\n");
    } */
  

    printf ("\n Deallocating memory \n\n");
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);

    printf (" Example completed. \n\n");
    PAPI_reset(eventset);
    return 0;
}
