#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#define NUM_EVENTS 1
#ifndef SIZE
#   define SIZE  
#endif

float matrix_a[SIZE][SIZE];
float vector_b[SIZE];
float vector_c[SIZE];

void init_array()
{
    int i, j;

    for (i = 0; i < SIZE; i++) {	
        vector_b[i] = (1+(i)%1024)/2.0;
	vector_c[i] = 0.0;
        for (j = 0; j < SIZE; j++) {
            matrix_a[i][j] = (1+(i*j)%1024)/2.0;
        }
    }
}


void vecmul()
{
        // Multiply matrix_a by vector_b
        int i, k;
        for (i = 0; i < SIZE; i++) {
                for (k = 0; k < SIZE; k++) {
                        vector_c[i] += matrix_a[i][k] * vector_b[k];
                }
        }
}


void reset_vector( void )
{
  int i;

  for( i = 0 ; i < SIZE ; i++){
		vector_c[i] = 0.0;
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

  printf("LoopType = vecmul \n");
  PAPI_start(eventset);
  start_time = PAPI_get_real_usec();
  vecmul();
  end_time = PAPI_get_real_usec();
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  reset_vector ();
  //printf("Done with Interchanged\n");
  printf("vecmul_time = %lli\n", end_time - start_time);
  printf("vecmul = %lli\n", values[0]);
  
  PAPI_reset(eventset);
    
  return 0;
}
