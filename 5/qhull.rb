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

command = 'rbox %d D%d | qhull'
dim_range = 2..3
point_range = 1e3..1e6

f = File.open('measurement.dat', 'w')

for dim in dim_range

    points = point_range.begin

    while points <= point_range.end

        print "calculating convex hull of " + points.to_s + " points in " + dim.to_s + "-D\n"
        output = IO.popen sprintf(command, points, dim)

        m = /CPU seconds to compute hull \(after input\): (.+)/.match output.read
        
        f.puts points.to_s + ' ' + m[1]
        
        points *= 10
    
    end
    f.puts "\n"
end

f.close

system "gnuplot -p -e 'set logscale x; plot \"measurement.dat\"'"
