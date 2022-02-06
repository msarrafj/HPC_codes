#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#define NUM_EVENTS 1
#define N 1000
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

void classic_matmul()
{
        // Multiply the two matrices
        int i, j, k;
        #pragma omp parallel for collapse(2)
        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        float sum = 0.0;
                        for (k = 0; k < N; k++) {
                                sum += matrix_a[i][k] * matrix_b[k][j];
                        }
                        matrix_c[i][j] = sum;
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
//#ifndef FLAG2
//#   define FLAG2  
//#endif
//#ifndef FLAG3
//#   define FLAG3  
//#endif

#define str(x)   #x
#define SHOW_DEFINE(x) printf("%s \t", str(x))

  PAPI_add_event(eventset, FLAG);
  //PAPI_add_event(eventset, FLAG2);
  //PAPI_add_event(eventset, FLAG3);
  //PAPI_add_event(eventset, a);	   
  //PAPI_add_event(eventset, a);
//Here we define event flags
// if (strcmp("-TCM", argv[1]) == 0)
//    {
//	    PAPI_add_event(eventset, PAPI_L1_TCM);
//	    PAPI_add_event(eventset, PAPI_L2_TCM);
//	    PAPI_add_event(eventset, PAPI_L3_TCM);
//	    printf("\n option TCM is found\n");
//    }
// else
//    {
//	    printf("Unknown option for PAPI %s\n\n", argv[1OL1WIDTH "s\t",
// }
// printf("created and added all events.\n");
  
// Initialize array
  init_array();


  printf("LoopType = Classic\n");
  PAPI_start(eventset);
  start_time = PAPI_get_real_usec();
  classic_matmul();
  end_time = PAPI_get_real_usec();
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  reset_matrix ();
  //printf("Done with Classic\n");
  printf("Classic_time = %lli\n", end_time - start_time);
  printf(" Classic = %lli\n", values[0]);
  PAPI_reset(eventset);
       
  reset_matrix();
  

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
  printf(" Interchanged = %lli\n", values[0]);
  //printf(" FLAG3 = %lli\n", values[2]);
  
  PAPI_reset(eventset);
    
  return 0;
}
