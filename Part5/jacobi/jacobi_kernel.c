#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define OFFSET(x, y, m) (((x)*(m)) + (y))

int main(int argc, char** argv)
{
    const int n = 1024;
    const int m = 1024;
    const int iter_max = 10;
    
    const double tol = 1.0e-6;
    double error = 1.0;

    double *restrict A    = (double*)malloc(sizeof(double)*n*m);
    double *restrict Anew = (double*)malloc(sizeof(double)*n*m);
    
    memset(A, 0, n * m * sizeof(double));
    memset(Anew, 0, n * m * sizeof(double));

    for(int i = 0; i < m; i++){
        A[i] = 1.0;
        Anew[i] = 1.0;
    }
        
    printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);
    
    double st = omp_get_wtime();
    int iter = 0;
    #pragma acc data copyin(A[0:n*m]) copyout(Anew[0:m*n]) 
    while ( error > tol && iter < iter_max )
    {
    double error = 0.0;

    #pragma acc kernels
{

    for( int j = 1; j < n-1; j++)
    {

        for( int i = 1; i < m-1; i++ )
        {
            Anew[OFFSET(j, i, m)] = 0.25 * ( A[OFFSET(j, i+1, m)] + A[OFFSET(j, i-1, m)]
                                           + A[OFFSET(j-1, i, m)] + A[OFFSET(j+1, i, m)]);
            error = fmax( error, fabs(Anew[OFFSET(j, i, m)] - A[OFFSET(j, i , m)]));
        }
    }
 
    for( int j = 1; j < n-1; j++)
    {

        for( int i = 1; i < m-1; i++ )
        {
            A[OFFSET(j, i, m)] = Anew[OFFSET(j, i, m)];    
        }
    }

}

        if(iter % 100 == 0) printf("%5d, %0.6f\n", iter, error);
        
        iter++;

    }

    double runtime = omp_get_wtime() - st;

; 
    printf("Total = %f s\n", runtime);

    free(A);
    free(Anew);

    return 0;
}

