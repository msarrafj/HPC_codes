CC = gcc
ICC = icc
OPT = -O0
OMP = -qopenmp

N = n
T = t
IN = i
OUT = o

all: allMat

allMat: allMat.c
	$(ICC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) allMat.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o allMat $(OMP)  -D SIZE=$(N) -D IN_THREADS=$(IN) -D OUT_THREADS=$(OUT) -dM -lm 



