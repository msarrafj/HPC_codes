#!/bin/bash
#SBATCH -N 56
#SBATCH --ntasks-per-node 1
#SBATCH -t 00:02:00
#SBATCH -o broad_red_output_56N_1n_2Min_process_pinning_bindByCore_mapByNode

declare -a Size=(1000000 10000000 100000000)
declare -a Proc=(2 4 8 16 32 56)
echo -e "Size \t dest=2 \t dest=4 \t dest=8 \t dest=16 \t dest32 \t dest56" | tee -a broadcast{Max,Min,Avg}.dat
echo -e "Size \t dest=2 \t dest=4 \t dest=8 \t dest=16 \t dest32 \t dest56" | tee -a reduce{Max,Min,Avg}.dat
for i in "${Size[@]}"
	do
	echo "size of data is $i B"
	echo -e -n "$i \t" | tee -a  broadcast{Max,Min,Avg}.dat
	echo -e -n "$i \t" | tee -a  reduce{Max,Min,Avg}.dat
	echo "broadcasting ..."
	mpicc broadcast.c -o broad -DN=$i
	mpicc reduce.c -o red -DN=$i
	for j in "${Proc[@]}"
		do
		echo "Broadcast ${j} processes"
		mpirun -np $j  --bind-to core --map-by node ./broad > ./result1

		echo "Reduce ${j} processes"
		mpirun -np $j  --bind-to core --map-by node ./red > ./result2

		awk '$1=="Max" {printf "%f\t", $3}'  ./result1 >> broadcastMax.dat
		awk '$1=="Max" {printf "%f\t", $3}' ./result2 >> reduceMax.dat
	
		
		awk '$1=="Min" {printf "%f\t", $3}'  ./result1 >> broadcastMin.dat
		awk '$1=="Min" {printf "%f\t", $3}' ./result2 >> reduceMin.dat
		

		awk '$1=="Avg" {printf "%f\t", $3}'  ./result1 >> broadcastAvg.dat
		awk '$1=="Avg" {printf "%f\t", $3}' ./result2 >> reduceAvg.dat
		
		rm ./result1 ./result2
	done
	echo -e -n "\n" | tee -a  broadcast{Max,Min,Avg}.dat
	echo -e -n "\n" | tee -a  reduce{Max,Min,Avg}.dat
	rm ./broad ./red
done
