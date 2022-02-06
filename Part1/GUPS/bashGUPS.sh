#!/bin/bash
declare -a N=(7 10 13 17 20 23 27 30)
declare -a optimize=("-O0" "-O1" "-O2" "-O3")

echo -e "optOption \t Vectorsize \t GUPs" >> ./results_trunc.dat
for i in "${N[@]}"
	do
	echo "N is of size: $i"
	echo "N is of size: $i" >> ./results_trunc.dat
	for j in "${optimize[@]}"
		do
		echo "Optize option is: $j"
		echo -n -e "$j \t" >> ./results_trunc.dat
		mpicc $j gups_vanilla.c -o gups_vanilla
		./gups_vanilla ${i} "$((4 * $i))" 512 >./results.dat
		rm ./gups_vanilla

		awk '$1=="Vector" {print $3}' ./results.dat > ./results1.dat
		awk '$1=="Gups:" {print $2}'  ./results.dat > ./results2.dat
		paste ./results1.dat ./results2.dat >> ./results_trunc.dat
		rm ./results1.dat ./results2.dat 
	done
done

