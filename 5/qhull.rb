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

dim = 4
points = 100000

print "calculating convex hull of " + points.to_s + " points in " + dim.to_s + "-D\n"
output = IO.popen 'rbox '+points.to_s+' D'+dim.to_s+' | qhull'

m = /CPU seconds to compute hull \(after input\): (.+)/.match output.read

p m[1]


