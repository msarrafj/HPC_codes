#!/bin/bash
declare -a Code=("bothSimple" "inner38" "innerReduction" "innerSumPrivate" "outerSimple")
declare -a Size=( 1024 )
declare -a Thread=( 4 8 14)


echo -e "Size \t Thread \t Code \t ExeTime \t L1-miss \t L2-miss \t L3-miss \t P1Power \t dramPower" >> ./result.dat 
for i in "${Size[@]}"
	do
	echo "size = $i"
	for j in "${Thread[@]}" 
		do
		echo "Threads_used = $j"
		for k in "${Code[@]}"
			do
			echo "-------------running $k code -----------------"
			echo -n -e "$i \t $j \t $k " > ./resultsA.dat

			make allMat N=$i T=$j
			module load papi
			
			sed -i "811s|.*|system(\" \.\/allMat $k \");|" rapl_read.c
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
