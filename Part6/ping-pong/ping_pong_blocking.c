#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
//#define N 100000000 //100000000 chars ~= 100MB

int main(int argc, char* argv[]) {
  int i,count=0,len;
  double start,end;
  char *array = (char*)malloc(sizeof(char)*N);
  char *recv = (char*)malloc(sizeof(char)*N);
  char response[10]="ping-pong";
 
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Find out rank, size
  int world_rank;
  int partner_rank[6] = {1,3,7,15,31,55};
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  //We are assuming at least 2 processes for this task
  if (world_size <= 2) {
    fprintf(stderr, "World size must be two for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  if(world_rank==0){
    for(i=0;i<N;array[i++]='a');
  }

  for(i=0;i<6;i++){
 
    if (world_rank == 0) {

      start = MPI_Wtime();

      MPI_Send(array, N, MPI_CHAR, partner_rank[i], 0, MPI_COMM_WORLD);

      MPI_Recv(response, 10, MPI_CHAR, partner_rank[i] , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      end = MPI_Wtime();
      printf("On process %d, For destination %d, Time = %f sec\n",world_rank+1, partner_rank[i]+1,end-start); 

    } else if(world_rank == partner_rank[i]){
      MPI_Recv(recv, N, MPI_CHAR, 0 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      
      MPI_Send(response, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

  }
  MPI_Finalize();
  exit(0);
}
