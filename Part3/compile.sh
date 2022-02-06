##How to compile

#rapl-read
gcc -O2 -Wall -o rapl-read rapl-read.c -lm

#quicksort
gcc quick_sort.c -o quicksort

#MKL Mul
icc -mkl mklMul.c -o mklMul
