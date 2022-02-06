#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define N 16384
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

void classic_vec_matmul()
{       
        int i, j, k;
	
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		for (j = 0; j < N; j++) {
                       	vector_c[i] += matrix_a[i][j] * vector_b[j];
		}
        }
}

int main(){
        int i,j;
        init_array();

	double start = omp_get_wtime(); 
        classic_vec_matmul();
	double end = omp_get_wtime();
	 
	printf("Time:%1.9f\n",end-start);
}
