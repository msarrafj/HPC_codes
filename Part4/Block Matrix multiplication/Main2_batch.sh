#!/bin/bash
declare -a Code=( "outerParal" "middleParal" "innerParal" )
declare -a Size=( 1024 2048)
declare -a Block=( 4 64 225 )
declare -a Thread=( 1 4 8 )

mkdir -p Output
for i in "${Size[@]}"
	do
	for l in "${Block[@]}"
		do
		echo "Blocks used = $l"
		file="matMul_${l}_${i}"
		echo -e "Thread \t outerParal \t middleParal \t innerParal" | tee ./Output/{Time,L1,L2,L3,Power,dram}_${file}.dat 
		echo "size = $i"
		for j in "${Thread[@]}" 
			do
			echo "Threads_used = $j"
			echo "$j" >> ./threads.dat
			for k in "${Code[@]}"
				do
				echo "-------------running $k code -----------------"

				make block_mm N=$i B=$l T=$j
				module load papi
				
				sed -i "811s|.*|system(\" \.\/block_mm $k \");|" rapl_read.c
				gcc -O2 -Wall -o rapl-read rapl_read.c -lm
				./rapl-read > ./resultsrun.dat
				rm ./rapl-read block_mm
				
				# dump segmentation faults as blank in outputs
				if ! grep -q "RUNNING" ./resultsrun.dat; then
  				echo "" | tee ./results{Time,L1,L2,L3,Power,dram}_${k}_${l}_${i}.dat
				else 
				awk '$1=="Time" {print $3}' ./resultsrun.dat >> ./resultsTime_${k}_${l}_${i}.dat
				awk '$1=="L1_misses" {print $3}' ./resultsrun.dat >> ./resultsL1_${k}_${l}_${i}.dat
				awk '$1=="L2_misses" {print $3}' ./resultsrun.dat >> ./resultsL2_${k}_${l}_${i}.dat
				awk '$1=="L3_misses" {print $3}' ./resultsrun.dat >> ./resultsL3_${k}_${l}_${i}.dat
				awk '$1=="package-0" {print substr($3, 1, length($3)-1)}' ./resultsrun.dat >> ./resultsPower_${k}_${l}_${i}.dat
				awk '$1=="dram" {print substr($3,1,length($3)-1);exit}' ./resultsrun.dat >>  ./resultsdram_${k}_${l}_${i}.dat
				fi
				rm ./resultsrun.dat
			done	
		done
				paste ./threads.dat ./resultsTime_outerParal_${l}_${i}.dat  ./resultsTime_middleParal_${l}_${i}.dat ./resultsTime_innerParal_${l}_${i}.dat>> ./Output/Time_${file}.dat
				paste ./threads.dat ./resultsL1_outerParal_${l}_${i}.dat  ./resultsL1_middleParal_${l}_${i}.dat ./resultsL1_innerParal_${l}_${i}.dat>> ./Output/L1_${file}.dat
				paste ./threads.dat ./resultsL2_outerParal_${l}_${i}.dat  ./resultsL2_middleParal_${l}_${i}.dat ./resultsL2_innerParal_${l}_${i}.dat>> ./Output/L2_${file}.dat
				paste ./threads.dat ./resultsL3_outerParal_${l}_${i}.dat  ./resultsL3_middleParal_${l}_${i}.dat ./resultsL3_innerParal_${l}_${i}.dat>> ./Output/L3_${file}.dat
				paste ./threads.dat ./resultsPower_outerParal_${l}_${i}.dat  ./resultsPower_middleParal_${l}_${i}.dat ./resultsPower_innerParal_${l}_${i}.dat>> ./Output/Power_${file}.dat
				paste ./threads.dat ./resultsdram_outerParal_${l}_${i}.dat  ./resultsdram_middleParal_${l}_${i}.dat ./resultsdram_innerParal_${l}_${i}.dat>> ./Output/dram_${file}.dat
		rm *.dat
	done
done
