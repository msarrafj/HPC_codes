#!/bin/bash
declare -a Flags=( $(cut -f 1 papi_ref.dat ) )
declare -a Size=(5000 25000 125000 625000 3125000 15625000 78125000)
#declare -a Flags=("PAPI_L1_TCM " "PAPI_L1_DCM ")

for i in "${Size[@]}"
	do 
	echo "size = $i"
	echo -e "Size \t Eventname \t  sorted \t ExeTime \t Desc \t P1Power \t dramPower" >> ./resultsorted.dat 
	for j in "${Flags[@]}"
		do
		echo "Eventname = $j"
		echo -n -e "$i \t $j \t" > ./resultsA.dat
		# PAPI event for sorted:
		make quick_sortPAPI N=$i F=$j
		module load papi
		srun ./quick_sortPAPI > ./resultsrun.dat
		rm quick_sortPAPI

		awk '$1=="sorted" {print $3}' ./resultsrun.dat >./resultsB.dat
		awk '$1=="sorted_time" {print $3}' ./resultsrun.dat >./resultsC.dat

		paste ./resultsA.dat ./resultsB.dat ./resultsC.dat >> ./resulttmpsorted.dat
		rm  ./resultsB.dat ./resultsC.dat 
done
		#  w/o PAPI event, but power comsumption for quick_sort
		make quick_sort N=$i
		gcc -O2 -Wall -o rapl-read rapl_read.c -lm
		srun ./rapl-read >> ./resultsrun.dat
		rm ./quick_sort ./rapl-read

		awk '$1=="package-0" {print $3}' ./resultsrun.dat > P1power.dat
		awk '$1=="dram" {print $3;exit}' ./resultsrun.dat > dram1power.dat

		paste ./resulttmpsorted.dat ./papi_ref.dat ./P1power.dat ./dram1power.dat| cut -f 1-5,7,8-9  >> ./resultsorted.dat
		rm ./resultsA.dat ./resultsrun.dat ./resulttmpsorted.dat ./P1power.dat ./dram1power.dat
done
