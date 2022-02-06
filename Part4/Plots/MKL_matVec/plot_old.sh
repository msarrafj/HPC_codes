#!/bin/bash
declare -a Size=(1024 4096 16384)
declare -a name=("Time" "L1" "L2" "L3" "Power" "dram")
mkdir -p Plots
for i in "${Size[@]}"
	do
	for j in "${name[@]}"
		do
		file3="${j}_mklMul"
		paste <(cut -f 1-2 ${file3}_1024.dat) <(cut -f 2 ${file3}_4096.dat) <(cut -f 2 ${file3}_16384.dat) > ${j}_out.dat
	done
done
