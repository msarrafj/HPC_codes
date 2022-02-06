#include <time.h>
#include <stdio.h>
#include <unistd.h>
int main(){

	clock_t start, end;
	int a,b,c;

	start = clock();
	printf("Start: %lf\n", start);
	for(int i=0; i<1000000; i++){
        	a=i;
		b=i+1;
		c=a+b;
	}	
	sleep(2);
	end = clock();
	printf("End: %lf\n", end);
	printf("CLOCKS_PER_SEC: %d\n",CLOCKS_PER_SEC);
	double sec = ((double)(end-start))/ CLOCKS_PER_SEC;
	printf("\nTime taken %lf seconds\n", sec);

	return 0;
}
