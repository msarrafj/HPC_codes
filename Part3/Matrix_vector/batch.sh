#!/bin/bash
declare -a Flags=( $(cut -f 1 papi_ref.dat ) )
declare -a Size=(500 1000 1500 2000 2500 3000 4000 5000)
#declare -a Flags=("PAPI_L1_TCM " "PAPI_L1_DCM ")

for i in "${Size[@]}"
	do 
	echo "size = $i"
	echo -e "Size \t Eventname \t  vecmul \t ExeTime \t Desc \t P1Power \t dramPower" >> ./resultVEC.dat 
	echo -e "Size \t Eventname \t  mkl \t ExeTime \t Desc \t P1Power \t dramPower" >> ./resultMKL.dat 
	for j in "${Flags[@]}"
		do
		echo "Eventname = $j"
		echo -n -e "$i \t $j \t" > ./resultsA.dat
		# PAPI event for matmul:
		make vecmulPAPI N=$i F=$j
		module load papi
		srun ./vecmulPAPI > ./resultsrun.dat
		rm vecmulPAPI

		awk '$1=="vecmul" {print $3}' ./resultsrun.dat >./resultsB.dat
		awk '$1=="vecmul_time" {print $3}' ./resultsrun.dat >./resultsC.dat

		paste ./resultsA.dat ./resultsB.dat ./resultsC.dat >> ./resulttmpVEC.dat
		rm  ./resultsB.dat ./resultsC.dat 
		# PAPI event for mKL:
		make mklMulPAPI N=$i F=$j
		module load papi
		srun ./mklMulPAPI > ./resultsrun.dat
		rm mklMulPAPI

		awk '$1=="mklMul" {print $3}' ./resultsrun.dat >./resultsB.dat
		awk '$1=="mklMul_time" {print $3}' ./resultsrun.dat >./resultsC.dat

		paste ./resultsA.dat ./resultsB.dat ./resultsC.dat >> ./resulttmpMKL.dat
		rm  ./resultsA.dat ./resultsB.dat ./resultsC.dat 
done
		#  w/o PAPI event, but power comsumption for matMul
		make vecmul N=$i
		sed -i 's/mklMul/vecmul/g' rapl_read.c
		gcc -O2 -Wall -o rapl-read rapl_read.c -lm
		srun ./rapl-read >> ./resultsrun.dat
		rm ./vecmul ./rapl-read

		awk '$1=="package-0" {print $3}' ./resultsrun.dat > P1power.dat
		awk '$1=="dram" {print $3;exit}' ./resultsrun.dat > dram1power.dat

		paste ./resulttmpVEC.dat ./papi_ref.dat ./P1power.dat ./dram1power.dat| cut -f 1-5,7,8-9  >> ./resultVEC.dat
		rm ./resultsrun.dat ./resulttmpVEC.dat ./P1power.dat ./dram1power.dat
		#  w/o PAPI event, but power comsumption for mklMul
		make mklMul N=$i
		sed -i 's/vecmul/mklMul/g' rapl_read.c
		gcc -O2 -Wall -o rapl-read rapl_read.c -lm
		srun ./rapl-read >> ./resultsrun.dat
		rm ./mklMul ./rapl-read

		awk '$1=="package-0" {print $3}' ./resultsrun.dat > P1power.dat
		awk '$1=="dram" {print $3;exit}' ./resultsrun.dat > dram1power.dat

		paste ./resulttmpMKL.dat ./papi_ref.dat ./P1power.dat ./dram1power.dat| cut -f 1-5,7,8-9  >> ./resultMKL.dat
		rm ./resultsrun.dat ./resulttmpMKL.dat ./P1power.dat ./dram1power.dat
done
