#include <stdio.h>
#include <stdlib.h>

int indx;

void initArray(int nelem_in_array, int *array);
void printArray(int nelem_in_array, int *array);
int squareArray(int nelem_in_array, int *array);

int main(void)
{
  const int nelem = 10;

  int *array1, *array2, *del;

/* Allocate memory for each array */
  array1 = (int *)malloc(nelem*sizeof(int));
  array2 = (int *)malloc(nelem*sizeof(int));
  del = (int *)malloc(nelem*sizeof(int));

/* Initialize array1 */
  initArray(nelem, array1);  
  
/* Print the elements of array1 */
  printf("array1 = ");
  printArray(nelem, array1);

/* Copy array1 to array2 */
  array2 = array1;

/* Pass array2 to the function 'squareArray( )' */
  squareArray(nelem, array2);

  printf("Squared array2\n");

  printArray(nelem, array2);

/* Compute difference between elements of array2 and array1 */ 
  for (indx = 0; indx < nelem; indx++)
  {
    del[indx] = array2[indx] - array1[indx];
  }

/* Print the computed differences */
  printf("The difference in the elements of array2 and array1 are:  ");
  printArray(nelem, del);

  free(array1);
  free(array2);
  free(del);

  return 0;
}

void initArray(const int nelem_in_array, int *array)
{
  for (indx = 0; indx < nelem_in_array; indx++)
  {
    array[indx] = indx + 2;
  }  
} 

int squareArray(const int nelem_in_array, int *array)
{
  int indx;

  for (indx = 0; indx < nelem_in_array; indx++)
  {
    array[indx] *= array[indx];
  }
  return *array;
}

void printArray(const int nelem_in_array, int *array)
{
  printf("[  ");

  for (indx = 0; indx < nelem_in_array; indx++)
  {
    printf("%d  ", array[indx]);
  } 
  printf("]\n\n");
}

