#! /bin/bash
declare -a Size=("SMALL" "MIDDLE" "LARGE")
mkdir -p Output
for i in "${Size[@]}"
	do
	echo -e "  $i" >> ./Output/${i}_results.dat 
	#Compiling
	pgcc -c -acc -fast -Minfo=accel himenoBMT.c -D ${Size} -D NN=15
	pgcc -acc -fast -ta=tesla:cc60 -Minfo=accel himenoBMT.o -o bmt
	#Get CPU performance data
	echo "============================
	     ========dram and flops========
	     ============================="
	nvprof --cpu-profiling on --metrics dram_read_transactions --metrics dram_write_transactions --metrics flop_count_dp ./bmt 2>&1 | tee CPU.dat
	

	awk '$1=="Device" {k=1;next};k && k++ <=8' CPU.dat | awk ' {print $2, "=" ,$9}' >> ./Output/${i}_results.dat

	awk '$1=="MFLOPS_measured" {print "MFLOPs =",$3}' CPU.dat >> ./Output/${i}_results.dat
	rm CPU.dat himenoBMT.o	
	rm ./bmt 
done
	paste -d ',' ./Output/SMALL_results.dat <(cut -f 3 -d ' ' ./Output/MIDDLE_results.dat) <(cut -f 3 -d ' ' ./Output/LARGE_results.dat) >> ./Output/final_CPU.dat 


