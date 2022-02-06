#!/bin/bash
#rm  ./results.dat
declare -a arraysize=(100 1000 10000 100000 1000000 10000000 100000000 1000000000)
declare -a optimize=("-O0" "-O1" "-O2" "-O3")

for i in "${arraysize[@]}"
	do
	echo "Array size is: $i"
	
	for j in "${optimize[@]}"
		do
		echo "Optize option is: $j"
		#echo "===========SIZEofArray is: ${i} and optimizeOPTion: ${j}" >>  ./rusults.dat 
		echo -n -e "${i} \t ${j} \t" >  ./results1.dat
		make SIZE=$i OPT=$j	
		./stream > ./results.dat
		rm stream


		awk '$1=="Copy:" {print $2}' ./results.dat >./results2_copy.dat
		awk '$1=="Scale:" {print $2}' ./results.dat > ./results2_scale.dat
		awk '$1=="Add:" {print $2}' ./results.dat > ./results2_add.dat
		awk '$1=="Triad:" {print $2}' ./results.dat > ./results2_triad.dat

		paste ./results1.dat ./results2_copy.dat >> ./results_copy.dat
		paste ./results1.dat ./results2_scale.dat >> ./results_scale.dat
		paste ./results1.dat ./results2_add.dat >> ./results_add.dat
		paste ./results1.dat ./results2_triad.dat >> ./results_triad.dat

		rm ./results.dat ./results2* ./results1.dat
	 done
done

