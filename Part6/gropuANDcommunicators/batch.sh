#!/bin/bash
#SBATCH -N 2
##SBATCH --ntasks-per-node 1
#SBATCH -t 00:01:00
#SBATCH -o output_sbatch_16Proc_on_2nodes_scramble
module load mpi/gcc_openmpi
echo "Run for 16 procs"
mpicc exercise3_4.c -o ex3_4
#mpirun -np 4 --rankfile rankfile ex3_4
mpirun -np 16 --map-by ppr:8:node ex3_4
echo "-----------------------------------------"
