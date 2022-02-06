#!/bin/bash
declare -a Code=( "middle_innner_Paral" "outer_inner_Paral" )
declare -a Size=( 1024 )
declare -a Block=( 16 1024 )
declare -a pairs=(16 96 32 80 56 56 80 32 96 16)
len=${#pairs[@]}

mkdir -p Output
for i in "${Size[@]}"
	do
	for l in "${Code[@]}"
		do
		echo " running $l code"
		file="matMul_${l}_${i}"
		echo -e "Thread \t 16 \t 1024" | tee ./Output/{Time,L1,L2,L3,Power,dram}_${file}.dat 
		echo "size = $i"
		 
		for (( j=0 ; j<${len} ; j+=2 ))
			do
			OUT=${pairs[j]}
			IN=${pairs[j+1]}
			echo "Threads_used OUT/IN= $OUT/$IN"
			for k in "${Block[@]}"
				do
				echo "-------------running for $k blocks -----------------"

				make block_mm N=$i B=$k OUT=$OUT IN=$IN
				module load papi
				
				sed -i "811s|.*|system(\" \.\/block_mm ${l} \");|" rapl_read.c
				gcc -O2 -Wall -o rapl-read rapl_read.c -lm
				./rapl-read > ./resultsrun.dat
				./rapl-read >> logs.dat
				rm ./rapl-read block_mm
				
				# dump segmentation faults as blank in outputs
				if ! grep -q "RUNNING" ./resultsrun.dat; then
  				echo "" | tee ./results{Time,L1,L2,L3,Power,dram}.dat
				else 
				awk '$1=="Time" {print $3}' ./resultsrun.dat >> ./resultsTime.dat
				awk '$1=="L1_misses" {print $3}' ./resultsrun.dat >> ./resultsL1.dat
				awk '$1=="L2_misses" {print $3}' ./resultsrun.dat >> ./resultsL2.dat
				awk '$1=="L3_misses" {print $3}' ./resultsrun.dat >> ./resultsL3.dat
				awk '$1=="package-0" {print substr($3, 1, length($3)-1)}' ./resultsrun.dat >> ./resultsPower.dat
				awk '$1=="dram" {print substr($3,1,length($3)-1);exit}' ./resultsrun.dat >>  ./resultsdram.dat
				fi
				rm ./resultsrun.dat
			done	
				paste <(echo "$OUT/$IN") <(tr '\n' '\t' < ./resultsTime.dat) >> ./Output/Time_${file}.dat
				paste <(echo "$OUT/$IN") <(tr '\n' '\t' < ./resultsL1.dat) >> ./Output/L1_${file}.dat
				paste <(echo "$OUT/$IN") <(tr '\n' '\t' < ./resultsL2.dat) >> ./Output/L2_${file}.dat
				paste <(echo "$OUT/$IN") <(tr '\n' '\t' < ./resultsL3.dat) >> ./Output/L3_${file}.dat
				paste <(echo "$OUT/$IN") <(tr '\n' '\t' < ./resultsPower.dat) >> ./Output/Power_${file}.dat
				paste <(echo "$OUT/$IN") <(tr '\n' '\t' < ./resultsdram.dat) >> ./Output/dram_${file}.dat
				rm  ./resultsTime.dat ./resultsL1.dat ./resultsL2.dat ./resultsL3.dat ./resultsPower.dat ./resultsdram.dat
		done
	done
done
