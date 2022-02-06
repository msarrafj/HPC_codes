CC = gcc
OPT = -O0
F = f


matmul: matmul.c
	$(CC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) matmul.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o matmul -DFLAG=$(F) -dM 

