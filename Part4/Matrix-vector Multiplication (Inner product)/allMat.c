#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "papi.h"
#define NUM_EVENTS 3

#ifndef SIZE
#define SIZE  
#endif

#ifndef THREADS
#define THREADS
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
	
	#pragma omp parallel for
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		#pragma omp parallel for
		for (j = 0; j < N; j++) {
                       	vector_c[i] += matrix_a[i][j] * vector_b[j];
		}
        }
}


void inner_38(int th)
{       
        int i, k;
	
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		int sum[th];
		#pragma omp parallel
		{	
			int j,id,nthrds;
			id = omp_get_thread_num();
			nthrds = omp_get_num_threads();
			for (j = id,sum[id]=0.0; j < N; j+=nthrds) {
                        	sum[id] += matrix_a[i][j] * vector_b[j];
			}
		}
		for(k=0; k<th; k++)
			vector_c[k] += sum[k];
        }
}



void inner_reduction()
{       
        int i;
	
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		float sum=0.0;
		#pragma omp parallel
		{	
			int j;
			#pragma omp for reduction(+:sum)
			for (j = 0; j < N; j++) {
                        	sum += matrix_a[i][j] * vector_b[j];
			}
			vector_c[i] = sum;
		}
        }
}



void inner_sum_private()
{       
        int i, k;
	
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		#pragma omp parallel
		{	
			int j,id,nthrds;
			float sum;
			id = omp_get_thread_num();
			nthrds = omp_get_num_threads();
			for (j = id, sum=0.0; j < N; j+=nthrds) {
                        	sum += matrix_a[i][j] * vector_b[j];
			}
		
			#pragma omp critical
			vector_c[i] += sum;
		}
        }
}



void outer_simple()
{       
        int i, j, k;
	
	#pragma omp parallel for
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		for (j = 0; j < N; j++) {
                       	vector_c[i] += matrix_a[i][j] * vector_b[j];
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
	printf("%d_threads_runned\n",THREADS);
	omp_set_num_threads(THREADS);
	// run
	start_time = PAPI_get_real_usec();
        if (strcmp (argv[1], "bothSimple") == 0){
		printf("BOTH SIMPLE CASE IS RUNNING\n");
		both_simple();
	}
        else if (strcmp (argv[1], "inner38") == 0){
		printf("INNER 38 CASE IS RUNNING\n");
		inner_38(THREADS);
	}
        else if (strcmp (argv[1], "innerReduction") == 0){
		printf("INNER REDUCTION CASE IS RUNNING\n");
		inner_reduction();
	}
        else if (strcmp (argv[1], "innerSumPrivate") == 0){
		printf("INNER SUM PRIVATE CASE IS RUNNING\n");
			inner_sum_private();
	}
     	else if (strcmp (argv[1], "outerSimple") == 0){
		printf("OUTER SIMPLE CASE IS RUNNING\n");
			outer_simple();
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
