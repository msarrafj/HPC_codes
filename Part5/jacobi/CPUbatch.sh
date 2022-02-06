#! /bin/bash
declare -a Size=(1024 2048 4096)
mkdir -p Output
for i in "${Size[@]}"
	do
	echo -e "  $i" >> ./Output/${i}_resultsCPU.dat 
	#Compiling
	pgcc -acc -fast -ta=tesla:cc60 -Minfo=accel jacobi.c -o jacobi -DSIZE=$i -DITERATIONS=20
	#Get CPU performance data
	echo "============================
	     ========dram and flops========
	     ============================="
	nvprof --cpu-profiling on --metrics dram_read_transactions --metrics dram_write_transactions --metrics flop_count_dp ./jacobi 2>&1 | tee CPU.dat
	
	awk '$1=="Device" {k=1;next};k && k++ <=12' CPU.dat | awk ' {print $2, "=" ,$9}' >> ./Output/${i}_resultsCPU.dat

	rm  CPU.dat	
	rm ./jacobi
done
	paste -d ',' ./Output/1024_resultsCPU.dat <(cut -f 3 -d ' ' ./Output/2048_resultsCPU.dat) <(cut -f 3 -d ' ' ./Output/4096_resultsCPU.dat) >> ./Output/final_CPU.dat 


