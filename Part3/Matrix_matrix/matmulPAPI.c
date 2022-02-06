#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#define NUM_EVENTS 1
#ifndef N
#   define N  
#endif
float matrix_a[N][N];
float matrix_b[N][N];
float matrix_c[N][N];

void init_array()
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matrix_a[i][j] = (1+(i*j)%1024)/2.0;
            matrix_b[i][j] = (1+(i*j)%1024)/2.0;
	    matrix_c[i][j] = 0.0;
        }
    }
}


void interchanged_matmul()
{
        // Multiply the two matrices
        int i, j, k;
        for (i = 0; i < N; i++) {
                for (k = 0; k < N; k++) {
                        for (j = 0; j < N; j++) {
                                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j                                                                                        ];
                        }
                }
        }
}


void reset_matrix( void )
{
  int i, j;

  for( i = 0 ; i < N ; i++){
	for ( j= 0 ; j < N ; j++)
	{
		matrix_c[i][j] = 0.0;
	}
}
}

int main(int argc,  char **argv[]){
  int i,j;
  float MR_L1 = 0.0f;
  long long start_time, end_time;
  long long values[NUM_EVENTS];
  int eventset = PAPI_NULL;
  PAPI_library_init(PAPI_VER_CURRENT);
  PAPI_create_eventset(&eventset);
#ifndef FLAG
#   define FLAG  
#endif


#define str(x)   #x
#define SHOW_DEFINE(x) printf("%s \t", str(x))

  PAPI_add_event(eventset, FLAG);
  init_array();

  printf("LoopType = Interchanged \n");
  PAPI_start(eventset);
  start_time = PAPI_get_real_usec();
  interchanged_matmul();
  end_time = PAPI_get_real_usec();
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  reset_matrix ();
  //printf("Done with Interchanged\n");
  printf("Interchanged_time = %lli\n", end_time - start_time);
  printf("Interchanged = %lli\n", values[0]);
  //printf(" FLAG3 = %lli\n", values[2]);
  
  PAPI_reset(eventset);
    
  return 0;
}
