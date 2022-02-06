CC = gcc
ICC = icc
OPT = -O0
OMP = -qopenmp

N = n
B = b
IN = i
OUT = o

all: block_mm

block_mm: block_mm.c
	$(ICC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) block_mm.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o block_mm $(OMP)  -D SIZE=$(N) -D BLOCK_SIZE=$(B) -D IN_THREADS=$(IN) -D OUT_THREADS=$(OUT) -dM -lm -qopenmp


block_mm_backup: block_mm_backup.c
	$(ICC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) block_mm_backup.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o block_mm_backup $(OMP)  -D SIZE=$(N) -D BLOCK_SIZE=$(B) -D THREADS=$(T) -dM -lm -qopenmp 


block1L: block1L.c
	$(ICC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) block1L.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o block1L $(OMP)  -D MATRIX_SIZE=$(N) -D BLOCK=$(B) -D NUMTHREADS=$(T) -dM -qopenmp 

