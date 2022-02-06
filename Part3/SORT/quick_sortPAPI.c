//Source code courtesy: internet

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "papi.h"
#define NUM_EVENTS 1
#ifndef SIZE	
#	define SIZE
#endif

float array_a[SIZE];
void quicksort(float*, int, int);

void init_array()
{
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < SIZE; i++) {
        array_a[i] = rand()*i*1024*2.0;
    }
}


int main()
{
  float MR_L1 = 0.0f;
  long long start_time, end_time;
  long long values[NUM_EVENTS];
  int eventset = PAPI_NULL;
  PAPI_library_init(PAPI_VER_CURRENT);
  PAPI_create_eventset(&eventset);
#ifndef FLAG
#   define FLAG  
#endif
  PAPI_add_event(eventset, FLAG);
  init_array();

  printf("LoopType = sorted \n");
  PAPI_start(eventset);
  start_time = PAPI_get_real_usec();
  quicksort(array_a, 0, SIZE-1);
  end_time = PAPI_get_real_usec();
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  //printf("Done with Interchanged\n");
  printf("sorted_time = %lli\n", end_time - start_time);
  printf("sorted = %lli\n", values[0]);
  //printf(" FLAG3 = %lli\n", values[2]);
  
  PAPI_reset(eventset);
  return 0;
}
void quicksort(float *arr, int low, int high)
{
  int pivot, i, j;
  float temp;

  if(low < high) {
    pivot = low; // select a pivot element
    i = low;
    j = high;
    while(i < j) {
      // increment i till you get a number greater than the pivot element
      while(arr[i] <= arr[pivot] && i <= high)
        i++;
      // decrement j till you get a number less than the pivot element
      while(arr[j] > arr[pivot] && j >= low)
        j--;
      // if i < j swap the elements in locations i and j
      if(i < j) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }

    // when i >= j it means the j-th position is the correct position
    // of the pivot element, hence swap the pivot element with the
    // element in the j-th position
    temp = arr[j];
    arr[j] = arr[pivot];
    arr[pivot] = temp;
    // Repeat quicksort for the two sub-arrays, one to the left of j
    // and one to the right of j
    quicksort(arr, low, j-1);
    quicksort(arr, j+1, high);
  }
}
