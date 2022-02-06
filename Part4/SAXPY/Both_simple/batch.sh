#!/bin/bash
declare -a pairs=(2 2 2 6 4 4 6 2 2 14 4 12 8 8 12 4 14 2 2 26 2 24 8 20 16 12 20 8 24 4 26 2 2 54 4 52 8 48 16 49 28 28 40 16 48 8 52 4 54 2 2 110 4 108 8 104 16 96 32 80 56 56 80 32 96 16 104 8 108 4 110 2)
declare -a Size=( 1024 4096 16384)
len=${#pairs[@]}
mkdir -p Output
for i in "${Size[@]}"
	do
	file="Saxpy_$i"
	echo -e "ThreadsO/I \t bothsimple" | tee ./Output/{Time,L1,L2,L3,Power,dram}_${file}.dat 
	echo "size = $i"
	for (( j=0 ; j<${len} ; j+=2 ))
		do
	    	OUT=${pairs[j]}
	   	IN=${pairs[j+1]}
		echo "Threads_used OUT/IN= $OUT/$IN"

		make allMat N=$i OUT=$OUT IN=$IN
		module load papi
				
		gcc -O2 -Wall -o rapl-read rapl_read.c -lm
		./rapl-read > ./resultsrun.dat
		rm ./rapl-read allMat
		
		paste <(echo "$OUT/$IN") <(awk '$1=="Time" {print $3}' ./resultsrun.dat) >> ./Output/Time_${file}.dat
		paste <(echo "$OUT/$IN") <(awk '$1=="L1_misses" {print $3}' ./resultsrun.dat) >> ./Output/L1_${file}.dat
		paste <(echo "$OUT/$IN") <(awk '$1=="L2_misses" {print $3}' ./resultsrun.dat) >> ./Output/L2_${file}.dat
		paste <(echo "$OUT/$IN") <(awk '$1=="L3_misses" {print $3}' ./resultsrun.dat) >> ./Output/L3_${file}.dat
		paste <(echo "$OUT/$IN") <(awk '$1=="package-0" {print substr($3, 1, length($3)-1)}' ./resultsrun.dat) >> ./Output/Power_${file}.dat
		paste <(echo "$OUT/$IN") <(awk '$1=="dram" {print substr($3,1,length($3)-1);exit}' ./resultsrun.dat) >>  ./Output/dram_${file}.dat
		done	
		rm  ./resultsrun.dat 
	done
