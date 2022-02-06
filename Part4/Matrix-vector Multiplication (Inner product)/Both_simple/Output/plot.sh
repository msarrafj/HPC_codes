#!/bin/bash
declare -a Size=(1024 4096 16384)
declare -a name=("Time" "L1" "L2" "L3" "Power" "dram")
mkdir -p Plots
for i in "${Size[@]}"
	do
	for j in "${name[@]}"
		do
		file="${j}_matVec_$i"
		gnuplot -persist <<-EOFMarker
		set terminal png size 800,500 enhanced font "Helvetica Neue,15"
		set output './Plots/${file}.png'

		red = "#FF0000"; green = "#00FF00"; blue = "#0000FF"; skyblue = "#87CEEB"; tearose = "#EB87CE";
		#set xrange [3:]
		set style data histogram
		set style histogram cluster gap 1
		set style fill solid
		set boxwidth 0.9
		set xtics format ""
		set xtics rotate
		set grid ytics
		set key Left
		set key autotitle columnhead

		set title "${j} for size of $i"
		plot "${file}.dat" using 2:xtic(1) title "Both-loop paral" linecolor rgb red
		EOFMarker
	done
done
