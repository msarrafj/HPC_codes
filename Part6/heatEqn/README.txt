1) This directory contains following files:
- heat.c : Code for 1D transient heat equaation with MPI.
- batch.sh : Script to compile and run heat.c with different processes and nx.
- README : this file.

2) The code is written to create 1D transient heat equation using jacobi method borrowed from https://people.sc.fsu.edu/~jburkardt/c_src/heat_mpi/heat_mpi.html. The code will be running with 2 4 8 16 28 proc and for nx of 100 100000 100000000, and fixed dt of 1/400.

