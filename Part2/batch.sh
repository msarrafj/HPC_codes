#!/bin/bash
declare -a Flags=( $(cut -f 1 papi_ref.dat ) )
#declare -a Flags=("PAPI_L1_TCM " "PAPI_L1_DCM ")

echo -e "Eventname \t Classical \t ExecutionTime \t Interchanged \t ExexutionTime" >> ./result.dat 
for i in "${Flags[@]}"
	do
	echo "Eventname = $i"
	echo -n -e "$i \t" > ./resultsA.dat
	make F=$i
	module load papi
	srun ./matmul > ./resultsrun.dat
	rm matmul

	awk '$1=="Classic" {print $3}' ./resultsrun.dat >./resultsB.dat
	awk '$1=="Classic_time" {print $3}' ./resultsrun.dat >./resultsC.dat
	awk '$1=="Interchanged" {print $3}' ./resultsrun.dat >./resultsD.dat
	awk '$1=="Interchanged_time" {print $3}' ./resultsrun.dat >./resultsE.dat

	paste ./resultsA.dat ./resultsB.dat ./resultsC.dat ./resultsD.dat ./resultsE.dat >> ./result.dat

	rm  ./resultsA.dat ./resultsB.dat ./resultsC.dat ./resultsD.dat ./resultsE.dat
done

