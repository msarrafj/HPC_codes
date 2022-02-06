CC = gcc
ICC = icc

OPT = -O0
F = f
N = n

all: quick_sort quick_sortPAPI 

quick_sortPAPI: quick_sortPAPI.c
	$(CC)  -I/opt/packages/papi/5.4.3/include/ $(OPT) quick_sortPAPI.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o quick_sortPAPI -DFLAG=$(F) -DSIZE=$(N) -dM 

quick_sort: quick_sort.c
	$(CC) quick_sort.c -o quick_sort -lm -DSIZE=$(N) 



