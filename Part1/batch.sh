#!/bin/bash
#SBATCH -N 1
#SBATCH -p RM-small
#SBATCH -t 05:00:00
#SBATCH --ntasks-per-node 4

srun ./helloworld
