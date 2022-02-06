#include <stdio.h>
#include <stdlib.h>
#ifndef N
#   define N  
#endif
float matrix_a[N][N];
float matrix_b[N][N];
float matrix_c[N][N];

void init_array()
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matrix_a[i][j] = (1+(i*j)%1024)/2.0;
            matrix_b[i][j] = (1+(i*j)%1024)/2.0;
	    matrix_c[i][j] = 0.0;
        }
    }
}


void interchanged_matmul()
{
        // Multiply the two matrices
        int i, j, k;
        for (i = 0; i < N; i++) {
                for (k = 0; k < N; k++) {
                        for (j = 0; j < N; j++) {
                                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j                                                                                        ];
                        }
                }
        }
}


void reset_matrix( void )
{
  int i, j;

  for( i = 0 ; i < N ; i++){
	for ( j= 0 ; j < N ; j++)
	{
		matrix_c[i][j] = 0.0;
	}
}
}

int main(int argc,  char **argv[]){
  int i,j;
  float MR_L1 = 0.0f;

  init_array();

  printf("Interchanged MM performed \n");
  interchanged_matmul();
  reset_matrix ();
    
  return 0;
}
