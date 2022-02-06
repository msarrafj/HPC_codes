#!/bin/bash
declare -a Code=("mklMul")
declare -a Size=( 1024 )
declare -a Thread=( 14)


echo -e "Code \t Size \t Thread \t ExeTime \t L1-miss \t L2-miss \t L3-miss \t P1Power \t dramPower" >> ./result.dat 
for k in "${Code[@]}"
	do
	echo "-------------running $k code -----------------"
	for i in "${Size[@]}"
		do
		echo "size = $i"
		for j in "${Thread[@]}" 
			do
			echo "Threads_used = $j"
			echo -n -e "$k \t $i \t $j \t" > ./resultsA.dat

			make allMat N=$i T=$j
			module load papi
			
			gcc -O2 -Wall -o rapl-read rapl_read.c -lm
			./rapl-read > ./resultsrun.dat
			rm ./rapl-read allMat
		
			awk '$1=="Time" {print $3}' ./resultsrun.dat >./resultsB.dat
			awk '$1=="Cache_misses" {print $3 "\t" $4 "\t" $5}' ./resultsrun.dat >./resultsC.dat
			awk '$1=="package-0" {print $3}' ./resultsrun.dat > P1power.dat
			awk '$1=="dram" {print $3;exit}' ./resultsrun.dat > dram1power.dat

			paste ./resultsA.dat ./resultsB.dat ./resultsC.dat P1power.dat dram1power.dat>> ./result.dat
			rm  ./resultsA.dat ./resultsB.dat ./resultsC.dat ./P1power.dat ./dram1power.dat

			
		done
	done
done
