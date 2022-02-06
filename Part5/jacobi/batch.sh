#! /bin/bash
declare -a Size=(1024 2048 4096)
mkdir -p Output
for i in "${Size[@]}"
	do
	echo -e "  $i" >> ./Output/${i}_results.dat 
	#Compiling
	pgcc -acc -fast -ta=tesla:cc35 -Minfo=accel jacobi.c -o jacobi -D SIZE=$i -D ITERATIONS=1000
	#Get GPU performance data
	echo "============================
	     ========system profiling=====
	     ============================="
	nvprof --system-profiling on ./jacobi 2>&1 | tee sys.dat
	#Get CPU performance data
	echo "============================
	     ========dram and flops========
	     ============================="
	#nvprof --cpu-profiling on --metrics dram_read_transactions --metrics dram_write_transactions --metrics flop_count_dp ./jacobi 2>&1 | tee CPU.dat
	
	awk '$1=="Total" {print "Total_time =",$3}' sys.dat >> ./Output/${i}_results.dat
	awk '$1=="Power" {print "AvgPower =",$4;exit}' sys.dat >> ./Output/${i}_results.dat 
	awk '$7 ~/CUDA/ {print "%_time_HtoD =", substr($1,1,length($1)-1)}' sys.dat | sed -n '1p'  >> ./Output/${i}_results.dat
	awk '$7 ~/CUDA/ {print "%_time_DtoH =", substr($1,1,length($1)-1)}' sys.dat | sed -n '2p' >> ./Output/${i}_results.dat
	awk  '$7 ~/main/ {print "%_time_loop1 =" , substr($1,1,length($1)-1)}' sys.dat | sed -n '1p'  >> ./Output/${i}_results.dat
	awk  '$7 ~/main/ {print "%_time_loop2 =" , substr($1,1,length($1)-1)}' sys.dat | sed -n '2p'  >> ./Output/${i}_results.dat

	awk '$1=="Device" {k=1;next};k && k++ <=12' CPU.dat | awk ' {print $2, "=" ,$9}' >> ./Output/${i}_results.dat

	rm sys.dat CPU.dat	
	rm ./jacobi
done
	paste -d ',' ./Output/1024_results.dat <(cut -f 3 -d ' ' ./Output/2048_results.dat) <(cut -f 3 -d ' ' ./Output/4096_results.dat) >> ./Output/final.dat 


