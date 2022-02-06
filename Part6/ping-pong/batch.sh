#!/bin/bash
#SBATCH -N 56
#SBATCH --ntasks-per-node 1
#SBATCH -t 00:01:00
#SBATCH -o output_56N_1taskPerNode_time1Min_process_pinning_bindByCore_mapByNode
declare -a Size=(1 10 100 1000 10000 100000 1000000 10000000)
echo -e "BLK-SIZE \t dest=2 \t dest=4 \t dest=8 \t dest=16 \t dest32 \t dest64" >> blocking.dat
echo -e "non-BLK-SIZE \t dest=2 \t dest=4 \t dest=8 \t dest=16 \t dest32 \t dest64" >> non-blocking.dat
for i in "${Size[@]}"
do
echo "size of data is $i B"
echo -e -n "$i" >> blocking.dat
echo -e -n "$i" >> non-blocking.dat
echo "Blocking"
mpicc ping_pong_blocking.c -o blocking -DN=$i
mpirun -np 56 --bind-to core --map-by node ./blocking > result1.dat

echo "NON Blocking"
mpicc ping_pong_non_blocking.c -o non_blocking -DN=$i
mpirun -np 56 --bind-to core --map-by node ./non_blocking > result2.dat
paste <(echo "$i") <(awk '$1=="On" {print $9}' ./result1.dat | sed -n '1p') <(awk '$1=="On" {print $9}' ./result1.dat | sed -n '2p') <(awk '$1=="On" {print $9}' ./result1.dat | sed -n '3p') <(awk '$1=="On" {print $9}' ./result1.dat | sed -n '4p')  <(awk '$1=="On" {print $9}' ./result1.dat | sed -n '5p') <(awk '$1=="On" {print $9}' ./result1.dat | sed -n '6p') >> blocking.dat

paste <(echo "$i") <(awk '$1=="On" {print $9}' ./result2.dat | sed -n '1p') <(awk '$1=="On" {print $9}' ./result2.dat | sed -n '2p') <(awk '$1=="On" {print $9}' ./result2.dat | sed -n '3p') <(awk '$1=="On" {print $9}' ./result2.dat | sed -n '4p')  <(awk '$1=="On" {print $9}' ./result2.dat | sed -n '5p') <(awk '$1=="On" {print $9}' ./result2.dat | sed -n '6p') >> non-blocking.dat

rm ./blocking ./non_blocking ./result1.dat ./result2.dat 
done
