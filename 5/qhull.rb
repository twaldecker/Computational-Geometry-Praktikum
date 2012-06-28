#!/bin/env ruby

print "Praktikum qhull\n"

# Aufgabe:
# Installieren Sie das Programm qhull, erzeugen Sie zufällige Punktemengen und berechnen Sie mit qhull konvexe Hüllen, auch in höheren Dimensionen (qhull bringt ein Werkzeug zur Erzeugung von Punktmengen mit). Plotten Sie die Zeiten für zunehmende Punktanzahlen bei unterschiedlichen Dimensionen (2-8). 

# Erzeugen von Punktmengen mit rbox:
# Angabe der Dimension mit Dn
# numerisches Argument ist Anzahl der Punkte
# Ausgabe: zeilenweise Punkte, koordinaten mit Space getrennt.
# z.B. Erzeugen von 15 Punkten im 8 Dimensionalen Raum:
# rbox 15 D8

dim_range = 2..8
point_range = 1e3..1e5

dim_point_range = Array.new()

dim_point_range[2] = 10..1e6
dim_point_range[3] = 10..1e5
dim_point_range[4] = 10..1e5
dim_point_range[5] = 10..1e4
dim_point_range[6] = 10..1e3
dim_point_range[7] = 10..1e3
dim_point_range[8] = 10..1e2

p dim_point_range

colors = ['#e0f0f0', '#c0e0f0', '#a0c0e0', '#80a0e0', '#4080e0', '#0020c0', '#4040a0']

f = File.open('measurement.dat', 'w')

for dim in dim_range

    points = dim_point_range[dim].begin
    
    f.puts "# #{dim}D (index #{dim-2})\n# X Y\n"

    while points <= dim_point_range[dim].end

        print "calculating convex hull of #{points} points in #{dim}-D\n"
        output = IO.popen "rbox #{points} D#{dim} | qhull"

        m = /CPU seconds to compute hull \(after input\): (.+)/.match output.read
        
        f.puts points.to_s + ' ' + m[1]
        
        points *= 10
    
    end
    f.puts "\n\n"
end

f.close

# Jetzt plotten wir die Ergebnisse mit gnuplot.

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
set xrange [1:1e6];
plot 'measurement.dat' index 0 with linespoints ls 1 title '2D', 
'' index 1 with linespoints ls 2 title '3D',
'' index 2 with linespoints ls 3 title '4D',
'' index 3 with linespoints ls 4 title '5D',
'' index 4 with linespoints ls 5 title '6D',
'' index 5 with linespoints ls 6 title '7D',
'' index 6 with linespoints ls 7 title '8D';"
GNUPLOT
