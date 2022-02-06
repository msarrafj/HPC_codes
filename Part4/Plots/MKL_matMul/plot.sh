#!/bin/bash
declare -a Size=(1024 2048)
declare -a name=("Time" "L1" "L2" "L3" "Power" "dram")
mkdir -p Plots
for i in "${Size[@]}"
	do
	for j in "${name[@]}"
		do
		file="${j}_out"
		gnuplot -persist <<-EOFMarker
		set terminal png size 800,500 enhanced font "Helvetica Neue,18"
		set output './Plots/${file}.png'

		yellow = "#FFFF00"; brown = "#8B0000"; dark_green = "#065535"; orange = "#FFA500"; red = "#FF0000"; green = "#00FF00"; blue = "#0000FF"; skyblue = "#87CEEB"; tearose = "#EB87CE";
		#set xrange [3:]
		set style data histogram
		set style histogram cluster gap 1
		set style fill solid
		set boxwidth 0.9
		set xtics format ""
		set grid ytics
		set key Left
		set key autotitle columnhead

		set title "${j}"
		plot "${file}.dat" using 2:xtic(1) title "matrixSize=1024" linecolor rgb tearose, \
		    '' using 3 title "matrixSize=2048" linecolor rgb dark_green
		EOFMarker
	done
done
