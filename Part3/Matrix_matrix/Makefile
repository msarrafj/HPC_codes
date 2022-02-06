CC = gcc
ICC = icc

OPT = -O0
F = f
N = n

all: matmulPAPI matmul mklMulPAPI mklMul

matmulPAPI: matmulPAPI.c
	$(CC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) matmulPAPI.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o matmulPAPI -DFLAG=$(F) -DN=$(N) -dM 

matmul: matmul.c
	$(CC) matmul.c -o matmul -lm -DN=$(N) 

mklMulPAPI: mklMulPAPI.c
	$(ICC) -mkl -I/opt/packages/papi/5.4.3/include/ $(OPT) mklMulPAPI.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o mklMulPAPI -DFLAG=$(F) -DSIZE=$(N) -dM


mklMul: mklMul.c
	$(ICC) -mkl mklMul.c -o mklMul -DSIZE=$(N)


