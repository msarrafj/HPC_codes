#!/bin/bash
#SBATCH -N 1
#SBATCH -n 28
#SBATCH -t 00:02:00
#SBATCH -o output_N2_n28
module load mpi/gcc_openmpi
echo -e "P \t time_dx1e2 \t time_dx1e5 \t time_dx1e8" > Time.dat
declare -a P=(1 2 4 8 16 28)
declare -a dx=(100 100000 100000000)
for j in "${dx[@]}"
	do
	echo "size of dx is $j"
	mpicc heat.c -o heat -lm -DN=$j
	for i in "${P[@]}"
		do
		echo "run for $i procs"
		mpirun -np $i heat > result.dat
		paste <(echo "$i") <(awk '$1=="Wall" {printf "%f\t", $6}' result.dat) >> Time_${j}.dat
		
	done
rm heat
done
paste <(cut -f 1-2 Time_100.dat) <(cut -f 2 Time_100000.dat) <(cut -f 2 Time_100000000.dat) >> Time.dat
