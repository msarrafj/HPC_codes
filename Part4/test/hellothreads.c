#include "omp.h"
#include <stdio.h>

int main()
{
omp_set_dynamic( 0 );
omp_set_num_threads( omp_num_procs() );
#pragma omp parallel
{
int ID = omp_get_thread_num(); 
printf("hello world from thread (%d) \n", ID);
}}
