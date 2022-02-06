#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <sys/time.h>

#define INDEX 10240

int main(int argc, char **argv) {
  
  float* matrixa = (float*)malloc(INDEX*INDEX*sizeof(float));
  float* matrixb = (float*)malloc(INDEX*INDEX*sizeof(float));
  float* mresult = (float*)malloc(INDEX*INDEX*sizeof(float));

  struct timeval start,finish;
  double duration;
  
  int i,j,k;

  /* Initialize the Matrix arrays */
  for ( i=0; i<INDEX*INDEX; i++ ){
    *(mresult+0+i) = 0.0;
    *(matrixa+0+i) = *(matrixb+0+i) = rand()*(float)1.1;
  }
  
  gettimeofday(&start, NULL);

  /* Matrix-Matrix multiply */
  for (i=0;i<INDEX;i++)
   for(j=0;j<INDEX;j++)
    for(k=0;k<INDEX;k++)
      *(mresult+i+j)=*(mresult+i+j) + *(matrixa+i+k)* *(matrixb+k+j);

  gettimeofday(&finish, NULL);

  duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;

  double gflops = 2.0 * INDEX * INDEX * INDEX;
  gflops = gflops/duration*1.0e-6;

  printf("Time taken: %lf seconds\n", duration);
  printf("GFLOPS = %lf\n", gflops/1000);
  
}

