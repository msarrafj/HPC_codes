#! /bin/bash
declare -a Size=("SMALL" "MIDDLE" )
mkdir -p Output
for i in "${Size[@]}"
	do
	echo -e "  $i" >> ./Output/${i}_results.dat 
	#Compiling
	pgcc -c -acc -fast -Minfo=accel himenoBMT.c -D ${Size}
	pgcc -acc -fast -ta=tesla:cc60 -Minfo=accel himenoBMT.o -o bmt
	#Get GPU performance data
	echo "============================
	     ========system profiling=====
	     ============================="
	nvprof --system-profiling on ./bmt 2>&1 | tee sys.dat
	#Get CPU performance data
	echo "============================
	     ========dram and flops========
	     ============================="
	nvprof --cpu-profiling on --metrics dram_read_transactions --metrics dram_write_transactions --metrics flop_count_dp ./bmt 2>&1 | tee CPU.dat
	
	awk '$1=="cpu_time" {print "Total_time =",$3}' sys.dat >> ./Output/${i}_results.dat
	awk '$1=="Power" {print "AvgPower =",$4;exit}' sys.dat >> ./Output/${i}_results.dat 
	awk '$7 ~/CUDA/ {print "%_time_HtoD =", substr($1,1,length($1)-1)}' sys.dat | sed -n '1p'  >> ./Output/${i}_results.dat
	awk '$7 ~/CUDA/ {print "%_time_DtoH =", substr($1,1,length($1)-1)}' sys.dat | sed -n '2p' >> ./Output/${i}_results.dat
	awk  '$7 ~/main/ {print "%_time_loop =" , substr($1,1,length($1)-1)}' sys.dat | sed -n '1p'  >> ./Output/${i}_results.dat

	awk '$1=="Device" {k=1;next};k && k++ <=8' CPU.dat | awk ' {print $2, "=" ,$9}' >> ./Output/${i}_results.dat

	#rm sys.dat CPU.dat	
	rm ./bmt
done
	paste -d ',' ./Output/SMALL_results.dat <(cut -f 3 -d ' ' ./Output/MIDDLE_results.dat) <(cut -f 3 -d ' ' ./Output/LARGE_results.dat) >> ./Output/final.dat 


