#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OFFSET(x, y, m) (((x)*(m)) + (y))
#define PI 3.14159265358979323846

void initialize(double *A, double *Anew, double *f, int m, int n)
{
    memset(A, 0, n * m * sizeof(double));
    memset(Anew, 0, n * m * sizeof(double));
    memset(f, 0, n  * sizeof(double));
int i,j;
    for( i = 0; i < m; i++){
        A[i] = 1.0;
        Anew[i] = 1.0;
    }

for ( j = 0; j < n; j++ )
  {
    double y = (double)j / ( double ) ( n - 1 );
    for ( i = 0; i < m; i++ )
    {
     double  x =  (float)i/(float)(m-1);
     double  f[OFFSET(j,i,m)]= (1.0);
	printf("f=%f",f);
    }
  }
}

double calcNext(double *A, double *Anew, double *f, int m, int n)
{
    double error = 0.0;
int i,j;
 

    for(  j = 0; j < n; j++)
    {
        for( i = 0; i < m; i++ )
        {
		if ( i == 0 || j == 0 || i == m - 1 || j == n - 1 )
	      {
		Anew[OFFSET(j, i, m)] = 0;
	      }
		else
		{
            Anew[OFFSET(j, i, m)] = 0.25 * ( A[OFFSET(j, i+1, m)] + A[OFFSET(j, i-1, m)]
                                           + A[OFFSET(j-1, i, m)] + A[OFFSET(j+1, i, m)]+f[OFFSET(j, i, m)]);
		}
            error = fmax( error, fabs(Anew[OFFSET(j, i, m)] - A[OFFSET(j, i , m)]));
        }
    }
    return error;
}
        
void swap(double *A, double *Anew, int m, int n)
{
int i,j;
    for(  j = 0; j < n; j++)
    {
        for( i = 0; i < m; i++ )
        {
            A[OFFSET(j, i, m)] = Anew[OFFSET(j, i, m)];    
        }
    }
}

void deallocate(double *A, double *Anew)
{
    free(A);
    free(Anew);
}


int main(int argc, char** argv)
{
    int i, j;
    const int n = 4;
    const int m = 4;
    const int iter_max = 10;
    
    const double tol = 1.0e-6;
    double error = 1.0;

    double *A    = (double*)malloc(sizeof(double)*n*m);
    double *Anew = (double*)malloc(sizeof(double)*n*m);
    double *f = (double*)malloc(sizeof(double)*n);
    
    initialize(A, Anew,f, m, n);
        
    printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);
    
    int iter = 0;
   
    while ( error > tol && iter < iter_max )
    {
        error = calcNext(A, Anew,f, m, n);
        swap(A, Anew, m, n);

        if(iter % 100 == 0) printf("%5d, %0.6f\n", iter, error);
        
        iter++;

    }

 

for ( j=0;j<n;j++){
for ( i=0; i<m; i++){
	printf("f[%d,%d]=%f \t",j,i,f[OFFSET(j,i,m)];} 
	printf("\n"); 
	
}
    deallocate(A, Anew);

    return 0;
}

