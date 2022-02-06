#!/bin/bash
declare -a Code=("inner38" "innerReduction" "innerSumPrivate" "outerSimple")
declare -a Size=( 1024 4096 16384 )
declare -a Thread=( 4 8 16 28 56 112 )

mkdir -p Output
for i in "${Size[@]}"
	do
	file="matVec_$i"
	echo -e "Thread \t inner38 \t innerReduction \t innerSumPrivate \t outerSimple" | tee ./Output/{Time,L1,L2,L3,Power,dram}_${file}.dat 
	echo "size = $i"
	for j in "${Thread[@]}" 
		do
		echo "Threads_used = $j"
		for k in "${Code[@]}"
			do
			echo "-------------running $k code -----------------"

			make allMat N=$i T=$j
			module load papi
			
			sed -i "811s|.*|system(\" \.\/allMat $k \");|" rapl_read.c
			gcc -O2 -Wall -o rapl-read rapl_read.c -lm
			./rapl-read > ./resultsrun.dat
			rm ./rapl-read allMat
		
			awk '$1=="Time" {print $3}' ./resultsrun.dat >> ./resultsTime.dat
			awk '$1=="L1_misses" {print $3}' ./resultsrun.dat >> ./resultsL1.dat
			awk '$1=="L2_misses" {print $3}' ./resultsrun.dat >> ./resultsL2.dat
			awk '$1=="L3_misses" {print $3}' ./resultsrun.dat >> ./resultsL3.dat
			awk '$1=="package-0" {print substr($3, 1, length($3)-1)}' ./resultsrun.dat >> Power.dat
			awk '$1=="dram" {print substr($3,1,length($3)-1);exit}' ./resultsrun.dat >>  dram.dat

		done	
			paste <(echo "$j") <(tr '\n' '\t' < ./resultsTime.dat) >> ./Output/Time_${file}.dat
			paste <(echo "$j") <(tr '\n' '\t' < ./resultsL1.dat) >> ./Output/L1_${file}.dat
			paste <(echo "$j") <(tr '\n' '\t' < ./resultsL2.dat) >> ./Output/L2_${file}.dat
			paste <(echo "$j") <(tr '\n' '\t' < ./resultsL3.dat) >> ./Output/L3_${file}.dat
			paste <(echo "$j") <(tr '\n' '\t' < ./Power.dat) >> ./Output/Power_${file}.dat
			paste <(echo "$j") <(tr '\n' '\t' < ./dram.dat) >> ./Output/dram_${file}.dat
			rm ./resultsrun.dat ./resultsTime.dat ./resultsL1.dat ./resultsL2.dat ./resultsL3.dat Power.dat dram.dat
	done
done
