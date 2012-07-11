#!/bin/env ruby
# encoding: utf-8

print "Praktikum qhull - plot results\n"

# Dieses Programm ruft gnuplot auf. Es kann mit $./plot.rb aufgerufen werden.

# die Farben für die Linien im Graph
colors = ['#e0f0f0', '#c0e0f0', '#a0c0e0', '#80a0e0', '#4080e0', '#0020c0', '#4040a0']

a = <<`GNUPLOT`
gnuplot -p -e "set style line 1 lc rgb '#{colors[0]}' lt 1 lw 2 pt 7 ps 1.5;
set style line 2 lc rgb '#{colors[1]}' lt 1 lw 2 pt 7 ps 1.5;
set style line 3 lc rgb '#{colors[2]}' lt 1 lw 2 pt 7 ps 1.5;
set style line 4 lc rgb '#{colors[3]}' lt 1 lw 2 pt 7 ps 1.5;
set style line 5 lc rgb '#{colors[4]}' lt 1 lw 2 pt 7 ps 1.5;
set style line 6 lc rgb '#{colors[5]}' lt 1 lw 2 pt 7 ps 1.5;
set style line 7 lc rgb '#{colors[6]}' lt 1 lw 2 pt 7 ps 1.5;
set logscale x;
set logscale y;
set xlabel 'Anzahl Punkte';
set ylabel 'Zeit in Sekunden';
set title 'Berechnung der Konvexen Hülle von Punktmengen im R^n';
set xrange [1:1e6];
plot 'measurement.dat' index 0 with linespoints ls 1 title '2D', 
'' index 1 with linespoints ls 2 title '3D',
'' index 2 with linespoints ls 3 title '4D',
'' index 3 with linespoints ls 4 title '5D',
'' index 4 with linespoints ls 5 title '6D',
'' index 5 with linespoints ls 6 title '7D',
'' index 6 with linespoints ls 7 title '8D';"
GNUPLOT
