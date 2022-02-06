#include <papi.h>
#include <omp.h>
#include <stdio.h>

void callee(int thr){

	int retval, EventSet=PAPI_NULL;
	long_long values[1];
	
	if (PAPI_create_eventset(&EventSet) != PAPI_OK)
		perror("Create event error\n");

	if (PAPI_add_event(EventSet, PAPI_TOT_INS) != PAPI_OK)
		perror("Add event error\n");
	
	if (PAPI_start(EventSet) != PAPI_OK)
		perror("Start error\n");

	int a=5, b=5;
	int c=0;
	c=b;
	b=a;
	a=c;
	
	if (PAPI_read(EventSet, values) != PAPI_OK)
    		perror("Read error\n");

	if (PAPI_stop(EventSet,values) != PAPI_OK)
		perror("Stop error\n");

	printf("After stopping the counters: %lld, Thread:%d\n",values[0],thr);
}

void main(){

	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
  		perror("Library init failed\n");
 
	if (PAPI_thread_init(omp_get_thread_num) != PAPI_OK)
		perror("Thread init failed\n");

	omp_set_num_threads(4);
	#pragma omp parallel
	{
		callee(omp_get_thread_num());
	}
}
