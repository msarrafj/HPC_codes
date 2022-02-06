CC = gcc
ICC = icc

OPT = -O0
F = f
N = n

all: vecmulPAPI vecmul mklMulPAPI mklMul

vecmulPAPI: vecmulPAPI.c
	$(CC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) vecmulPAPI.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o vecmulPAPI -DFLAG=$(F) -DSIZE=$(N) -dM 

vecmul: vecmul.c
	$(CC) vecmul.c -o vecmul -lm -DSIZE=$(N) 

mklMulPAPI: mklMulPAPI.c
	$(ICC) -mkl -I/opt/packages/papi/5.4.3/include/ $(OPT) mklMulPAPI.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o mklMulPAPI -DFLAG=$(F) -DSIZE=$(N) -dM


mklMul: mklMul.c
	$(ICC) -mkl mklMul.c -o mklMul -DSIZE=$(N)


