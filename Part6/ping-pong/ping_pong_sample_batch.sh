#!/bin/bash
#SBATCH -N 56
##SBATCH -n 56
#SBATCH --ntasks-per-node 1
#SBATCH -t 00:01:00
#SBATCH -o output_56N_56n_1taskPerNode_time1Min_process_pinning_bindByCore_mapByNode

echo "Blocking"
mpirun -np 56 --bind-to core --map-by node ./blocking

echo "NON Blocking"
mpirun -np 56 --bind-to core --map-by node ./non_blocking
