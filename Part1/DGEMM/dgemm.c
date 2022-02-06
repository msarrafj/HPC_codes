#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
  int i;
  
  if(argc<4){
    printf("Input Error\n");
    return 1;
  }

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  int sizeofa = m * k;
  int sizeofb = k * n;
  int sizeofc = m * n;
  
  
  double alpha = 1.2;
  double beta = 0.001;

  struct timeval start,finish;
  double duration;

  double* A = (double*)malloc(sizeof(double) * sizeofa);
  double* B = (double*)malloc(sizeof(double) * sizeofb);
  double* C = (double*)malloc(sizeof(double) * sizeofc);

  for (i=0; i<sizeofa; i++)
    A[i] = i%3+1;

  for (i=0; i<sizeofb; i++)
    B[i] = i%3+2;

  for (i=0; i<sizeofc; i++)
    C[i] = i%3+3;

  gettimeofday(&start, NULL);

  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,m,n,k,alpha,A, k, B, n,beta,C,n);

  gettimeofday(&finish, NULL);

  duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;

  double gflops = 2.0 * m *n*k;
  gflops = gflops/duration*1.0e-6;
 
  printf("Time taken: %lf seconds\n", duration);
  printf("GFLOPS = %lf\n", gflops/1000);

  return 0;
}
