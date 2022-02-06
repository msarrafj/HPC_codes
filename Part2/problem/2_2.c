#include <stdio.h>
#include <math.h>
#ifndef IMAX
#define IMAX 2001
#endif /* !IMAX */
#ifndef JMAX
#define JMAX 2001
#endif /* !JMAX */
#ifndef UMAX
#define UMAX 1.0
#endif /* !UMAX */
#ifndef EPSILON
#define EPSILON 0.00001
#endif /* !EPSILON */
#ifndef PI
#define PI 3.141596256
#endif /* !PI */
#define max(a,b) ((a>b)?a:b)
int main(int argc, char *argv[])
{
 double u[IMAX][JMAX];
 double du[IMAX][JMAX];
 double dumax=1.0+EPSILON;
 int i,j,it;
 /* Initialize u */
 for (i=0;i<IMAX;i++)
 {
 for (j=0;j<(JMAX-1);j++)
 {
 u[i][j]=0.0;
 }
 u[i][JMAX-1]=UMAX*sin(PI*(float)(i)/(float)(IMAX-1));
 }
 /* Main loop */
 it=0;
 while ( ( dumax>EPSILON && it<1000 ) )
 {
 dumax=0.0;
 for (i=1;i<(IMAX-1);i++)
 {
 for (j=1;j<(JMAX-1);j++)
 {
 du[i][j]=(u[i-1][j]+u[i+1][j]+u[i][j-1]+u[i][j+1])/4.0-u[i][j];
 dumax=max(dumax,fabs(du[i][j]));
 //for (i=1;i<(IMAX-1);i++)
 //for (j=1;j<(JMAX-1);j++)
 u[i][j]+=du[i][j];
 }}
it++;
 }
 printf("e=%le after %d iterationsn",dumax,it);
 return(it);
}
