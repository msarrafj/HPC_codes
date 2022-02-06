#!/bin/bash
declare -a Size=(1024 4096 16384)
declare -a name=("Time" "L1" "L2" "L3" "Power" "dram")
mkdir -p Plots
for i in "${Size[@]}"
	do
	for j in "${name[@]}"
		do
		file1="${j}_matVec_$i"
		file2="${j}_Saxpy_$i"
		file3="${j}_mklMul_$i"
		paste <(cut -f 1-5 ${file1}.dat) <(cut -f 2-4 ${file2}.dat) <(cut -f 2 ${file3}.dat) > ${j}_out_$i.dat
	done
done
