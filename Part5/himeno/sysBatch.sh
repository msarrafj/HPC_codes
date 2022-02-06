#! /bin/bash
declare -a Size=("SMALL" "MIDDLE" "LARGE")
mkdir -p Output
for i in "${Size[@]}"
	do
	echo -e "  $i" >> ./Output/${i}_results_sys.dat 
	#Compiling
	pgcc -c -acc -fast -Minfo=accel himenoBMT.c -D ${Size} -D NN=15
	pgcc -acc -fast -ta=tesla:cc60 -Minfo=accel himenoBMT.o -o bmt
	#Get GPU performance data
	echo "============================
	     ========system profiling=====
	     ============================="
	nvprof --system-profiling on ./bmt 2>&1 | tee sys.dat
	
	awk '$1=="cpu_time" {print "Total_time =",$3}' sys.dat >> ./Output/${i}_results_sys.dat
	awk '$1=="Power" {print "AvgPower =",$4;exit}' sys.dat >> ./Output/${i}_results_sys.dat 
	awk '$7 ~/CUDA/ {print "%_time_HtoD =", substr($1,1,length($1)-1)}' sys.dat | sed -n '1p'  >> ./Output/${i}_results_sys.dat
	awk '$7 ~/CUDA/ {print "%_time_DtoH =", substr($1,1,length($1)-1)}' sys.dat | sed -n '2p' >> ./Output/${i}_results_sys.dat
	awk  '$7 ~/jacobi/ {print "%_time_loop_1 =" , substr($1,1,length($1)-1)}' sys.dat | sed -n '1p'  >> ./Output/${i}_results_sys.dat
	awk  '$7 ~/jacobi/ {print "%_time_loop_2 =" , substr($1,1,length($1)-1)}' sys.dat | sed -n '2p'  >> ./Output/${i}_results_sys.dat
	awk  '$7 ~/jacobi/ {print "%_time_loop_3 =" , substr($1,1,length($1)-1)}' sys.dat | sed -n '3p'  >> ./Output/${i}_results_sys.dat

	rm  himenoBMT.o	
	rm ./bmt
done
	paste -d ',' ./Output/SMALL_results_sys.dat <(cut -f 3 -d ' ' ./Output/MIDDLE_results_sys.dat) <(cut -f 3 -d ' ' ./Output/LARGE_results_sys.dat) >> ./Output/final_sys.dat 


