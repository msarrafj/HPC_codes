/*--Include standard I/O C header file */
#include <stdio.h>
#include "math.h"
/*--Include the MPI header file */
#include "mpi.h"
#include <malloc.h>
//#define N 100000000 //100000000 elements of CHAR ~= 100MB data

/*--Template for MPI Programs in C */

int main( int argc, char* argv[])
{
/*--Declare all variables and arrays. */
     	char *array;
      	int myid,numprocs,i;
	double start, end;
	double local_time, global_max_time, global_min_time, global_sum_time;

	array = (char*)malloc(sizeof(char)*N);
	
	MPI_Init(&argc,&argv);        /* --> Required statement */
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	//TODO: Change condition of following "if" statement accordingly
	//to randomly select a source process instead of zero.
 	//initialize array on root process
        if(myid==0){
        	for(i=0;i<N;array[i++]='a');
        }
 
start = MPI_Wtime();

      	MPI_Bcast(array, N, MPI_CHAR, 0, MPI_COMM_WORLD);
      	
end = MPI_Wtime();

	local_time = end-start;

	//Get MAX time out of all local times
	MPI_Reduce(&local_time, &global_max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	//Get MIN time out of all local times
	MPI_Reduce(&local_time, &global_min_time, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	//Get sum of all local times, then divide it by numprocs to get average time.
	MPI_Reduce(&local_time, &global_sum_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


	if(myid==0){
		MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
		printf("Max time: %f seconds.\nMin Time: %f seconds.\nAvg Time: %f seconds.\n",global_max_time,global_min_time,(global_sum_time/numprocs)); 
	}
/*--Finilize MPI */
      	MPI_Finalize();              /* ---> Required statement */
	free(array);
      	return 0;
} 

