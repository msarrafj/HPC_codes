#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "papi.h"
#define NUM_EVENTS 3

#ifndef SIZE
#define SIZE  
#endif

#ifndef IN_THREADS
#define IN_THREADS
#endif

#ifndef OUT_THREADS
#define OUT_THREADS
#endif

#define N SIZE

float matrix_a[N][N];
float vector_b[N];
float vector_c[N];

void init_array()
{
    int i, j;

    for (i = 0; i < N; i++) {
     	vector_b[i] = (1+(i)%1024)/2.0;
	for (j = 0; j < N; j++) {
            matrix_a[i][j] = (1+(i*j)%1024)/2.0;
        }
    }
}

void both_simple()
{       
        int i, j, k;
	
	#pragma omp parallel for num_threads(OUT_THREADS)
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		//printf("inner Thread rank: %d\n", omp_get_thread_num());
		#pragma omp parallel for num_threads(IN_THREADS)
		for (j = 0; j < N; j++) {
                       	vector_c[i] += matrix_a[i][j] * vector_b[j];
			//printf("outer Thread rank: %d\n", omp_get_thread_num());
		}
        }
}



int main(int argc, char **argv){
        int i,j;
	long long start_time, end_time;
	long long values[NUM_EVENTS];
	int eventset = PAPI_NULL;
	PAPI_library_init(PAPI_VER_CURRENT);
	PAPI_create_eventset(&eventset);
	PAPI_add_event(eventset, PAPI_L1_TCM);
	PAPI_add_event(eventset, PAPI_L2_TCM);
	PAPI_add_event(eventset, PAPI_L3_TCM);
        init_array();

	printf("Code = %s\n",argv[0]);
	PAPI_start(eventset);
	//printf("%d_threads_runned\n",THREADS);
	//omp_set_num_threads(THREADS);
	// run
	start_time = PAPI_get_real_usec();
        if (strcmp (argv[1], "bothSimple") == 0){
		printf("BOTH SIMPLE CASE IS RUNNING\n");
		both_simple();
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
return(0); 
}
