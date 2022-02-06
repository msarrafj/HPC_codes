#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define N 4
float matrix_a[N][N];
float vector_b[N];
float vector_c[N];
void init_array()
{
    int i, j;

    for (i = 0; i < N; i++) {
	vector_c[i]=1;
	vector_b[i]=0;
	for(j = 0; j < N; j++){
		matrix_a[i][j] = 1;
	}
    }
}

void display()
{
    int i, j;
    printf("A\n");
    for (i = 0; i < N; i++) {
        for(j = 0; j < N; j++){
                printf("%f ",matrix_a[i][j]);
        }
	printf("\n");
    }
    printf("C\n");
    for(i=0; i<N; i++){
        printf("%f ",vector_c[i]);
    }
    printf("\nB\n");
    for(i=0; i<N; i++){
	printf("%f ",vector_b[i]);
    }
    printf("\n");
}

void saxpy()
{       
	int i,j;
       	for( j=0; j<N; j++){
        	for(i=0; i<N; i++){
                	vector_b[i] = matrix_a[i][j]*vector_c[j]+vector_b[i];
            }
        }
}

int main(){
        int i,j;
        init_array();

	omp_set_num_threads(28);
	double start = omp_get_wtime(); 
        saxpy();
	double end = omp_get_wtime();
	display();
	printf("Time:%1.9f\n",end-start);
}
