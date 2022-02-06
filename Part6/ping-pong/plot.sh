#!/bin/bash
declare -a name=("blocking" "non-blocking" )
mkdir -p Plots
for j in "${name[@]}"
	do
	file="${j}"
	gnuplot -persist <<-EOFMarker
	set terminal png size 800,500 enhanced font "Helvetica Neue,14"
	set output './Plots/${file}.png'

	red = "#FF0000"; green = "#00FF00"; blue = "#0000FF"; skyblue = "#87CEEB"; tearose = "#EB87CE"; gold = "#FFD700"
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

	set title "Results for  $j"
	plot "${file}.dat" using 2:xtic(1) title "to proc 2" linecolor rgb red, \
	    '' using 3 title "to proc 4" linecolor rgb green,\
	    '' using 4 title "to proc 8" linecolor rgb blue,\
	    '' using 5 title "to proc 16" linecolor rgb skyblue,\
	    '' using 6 title "to proc 32" linecolor rgb tearose,\
	    '' using 7 title "to proc 64" linecolor rgb gold
	
EOFMarker
done
