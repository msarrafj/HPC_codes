!/bin/bash
declare -a Size=(1024 4096 16384)
declare -a name=("Time" "L1" "L2" "L3" "Power" "dram")
mkdir -p Plots
for i in "${Size[@]}"
	do
	for j in "${name[@]}"
		do
		file="${j}_out_$i"
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

		set title "${j} for size of $i"
		plot "${file}.dat" using 2:xtic(1) title "inner38" linecolor rgb red, \
		    '' using 3 title "innerReduction" linecolor rgb blue, \
		    '' using 4 title "innerSumPrivate" linecolor rgb green, \
		    '' using 5 title "outerSimple" linecolor rgb skyblue, \
		    '' using 6 title "SaxpyInnerSimple" linecolor rgb brown, \
		    '' using 7 title "SaxpyOuterCritical" linecolor rgb yellow, \
		    '' using 8 title "SaxpyOuterSimple" linecolor rgb dark_green, \
		    '' using 9 title "MKL" linecolor rgb tearose
		EOFMarker
	done
done
