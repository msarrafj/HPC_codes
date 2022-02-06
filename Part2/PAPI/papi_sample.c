#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#define NUM_EVENTS 2
//Array declaration
double *A, *B, *C;
int dimension;

void simple_multiply(void);
void block_multiply(int);
void reset_matrix (void);

int main(int argc, char **argv)
{
  int i,j;
  float MR_L1 = 0.0f;
  long long start_time, end_time;
  long long values[NUM_EVENTS];
  long long values1[NUM_EVENTS];
  int eventset = PAPI_NULL;
  int eventset1 = PAPI_NULL;
  PAPI_library_init(PAPI_VER_CURRENT);
  PAPI_create_eventset(&eventset);
  PAPI_add_event(eventset, PAPI_L1_TCM);
  printf("created and added events.\n");

  if ( argc < 2) {
    printf("Usage: matmul <dimension>\n");
    exit(-1);
  }
        
  dimension = atoi(argv[1]);
    
  A = (double*)malloc(dimension*dimension*sizeof(double));
  B = (double*)malloc(dimension*dimension*sizeof(double));
  C = (double*)malloc(dimension*dimension*sizeof(double));
  if ( NULL == A || NULL == B || NULL == C ) {
    printf("Could not allocate memory. Aborting \n");
    exit (-1);
  }

  //Initialize the arrays with random values
  for(i = 0; i < dimension; i++) {
    for(j = 0; j < dimension; j++) {
      A[dimension*i+j] = (rand()/(RAND_MAX + 1.0));
      B[dimension*i+j] = (rand()/(RAND_MAX + 1.0));
      C[dimension*i+j] = 0.0;
    }
  }

  printf("***********************************simple multiply**********************************************\n");
  PAPI_start(eventset);
  start_time = PAPI_get_real_usec();
  simple_multiply();
  end_time = PAPI_get_real_usec();
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  reset_matrix ();
  printf("Done with simple multiply\n");
  printf("L1 cache misses = %lli\nexecution time = %lli\n ", values[0], end_time - start_time);
  PAPI_reset(eventset);

  /* Reset the result matrix to zero */



  free(A);
  free(B);
  free(C);
  return 0;
}

void simple_multiply ( void )
{
    int i, j, k;

    for(i = 0; i < dimension; i++) {
      for(j = 0; j < dimension; j++) {
 for(k = 0; k < dimension; k++) {
   C[dimension*i+j] += A[dimension*i+k] *
     B[dimension*k+j];
 }
      }
    }

    return;
}

void block_multiply ( int block )
{
    int i, j, k, p, q, r;
    int block_i, block_j, block_k;
    int num_blocks = dimension / block;

    for(i = 0; i < num_blocks; i++)  {
        block_i = i * block;
        for(j = 0; j < num_blocks; j++)  {
            block_j = j * block;
            for(k = 0; k < num_blocks; k++) {
                block_k = k * block;
                
                for (p=block_i; p < block_i+block; p++)
                    for (q=block_j; q < block_j+block; q++)
                        for (r=block_k; r < block_k+block; r++)
                            C[dimension*p+q] += A[dimension*p+r] *
                                B[dimension*r+q];
            }
        }
    }

    return;
}

void reset_matrix ( void )
{
  int i, j;

  for(i = 0; i < dimension; i++) {
    for(j = 0; j < dimension; j++) {
      C[dimension*i+j] = 0.0;
    }
  }

  return;
}
