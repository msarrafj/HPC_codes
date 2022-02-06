#!/bin/bash
#rm  ./results.dat
declare -a arraysize=(10 40 160 640 2560 10240 20480)

echo -e "ArraySize \t Time \t GFLIPS" >> ./results_trunc.dat	
for i in "${arraysize[@]}"
	do
	echo "Array size is: $i"
	echo -e -n "$i \t" >>  ./results_trunc.dat
	icc -o dgemm dgemm.c -I /opt/packages/OpenBLAS/0.2.19/include/ -L /opt/packages/OpenBLAS/0.2.19/lib -lopenblas
	./dgemm $i $i $i > ./results.dat
	rm dgemm

	awk '$1=="Time" {print $3}' ./results.dat > ./results1.dat
	awk '$1=="GFLOPS" {print $3}' ./results.dat > ./results2.dat
	paste ./results1.dat ./results2.dat >> ./results_trunc.dat
	rm ./results1.dat ./results2.dat ./results.dat
done

