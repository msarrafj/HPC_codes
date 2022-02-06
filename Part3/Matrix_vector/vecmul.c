#include <stdio.h>
#include <stdlib.h>
#ifndef SIZE
#   define SIZE  
#endif
float matrix_a[SIZE][SIZE];
float vector_b[SIZE];
float vector_c[SIZE];

void init_array()
{
    int i, j;

    for (i = 0; i < SIZE; i++) {	
        vector_b[i] = (1+(i)%1024)/2.0;
	vector_c[i] = 0.0;
        for (j = 0; j < SIZE; j++) {
            matrix_a[i][j] = (1+(i*j)%1024)/2.0;
        }
    }
}


void vecmul()
{
        // Multiply matrix_a by vector_b
        int i, k;
        for (i = 0; i < SIZE; i++) {
                for (k = 0; k < SIZE; k++) {
                        vector_c[i] += matrix_a[i][k] * vector_b[k];
                }
        }
}


void reset_vector( void )
{
  int i;

  for( i = 0 ; i < SIZE ; i++){
		vector_c[i] = 0.0;
}
}

int main(int argc,  char **argv[]){
  int i,j;
  float MR_L1 = 0.0f;

  init_array();

  printf("Vector_matrix performed \n");
  vecmul();
  reset_vector();
    
  return 0;
}
