#!/bin/env ruby
# encoding: utf-8

print "Praktikum qhull\n"

# Aufgabe:
# Installieren Sie das Programm qhull, erzeugen Sie zufällige Punktemengen und berechnen Sie mit qhull konvexe Hüllen, auch in höheren Dimensionen (qhull bringt ein Werkzeug zur Erzeugung von Punktmengen mit). Plotten Sie die Zeiten für zunehmende Punktanzahlen bei unterschiedlichen Dimensionen (2-8). 

# Ergebnis:
# Um einen sinnvollen Plot zu erhalten in dem die Informationen gut dargestellt werden wurden logarithmische Achsen für die Punkte und die Zeit gewählt.
# Im Plot mit doppelt logarithmischer Darstellung erhalten wir Geraden. Die Steigung der Geraden steigt mit zunehmender Anzahl an Dimensionen. Geraden in einer doppelt logarithmischen Darstellung ergeben eine Komplexität x^n. Wobei n mit der Steigung der Geraden zusammenhängt.
# Die meiste Rechenzeit in dem Programm wird benötigt um die Punktmengen zu erzeugen. Die Punktmengen brauchen auch sehr viel Arbeitsspeicher. Dadurch das die Punkte per Pipe an qhull übergeben werden braucht ein Punkt pro Dimension etwa -0.01073880122111999 20 Zeichen. 

#---

# Erzeugen von Punktmengen mit rbox:
# Angabe der Dimension mit Dn
# numerisches Argument ist Anzahl der Punkte
# Ausgabe: zeilenweise Punkte, koordinaten mit Space getrennt.
# z.B. Erzeugen von 15 Punkten im 8 Dimensionalen Raum:
# rbox 15 D8

# festlegen der Dimensionen
dim_range = 2..8

# festlegen der Start- und Endanzahl an Punkten in den verschiedenen Dimensionen.
dim_point_range = Array.new()

dim_point_range[2] = 3e4..1e6
dim_point_range[3] = 1e4..1e5
dim_point_range[4] = 1e3..1e5
dim_point_range[5] = 1e2..1e4
dim_point_range[6] = 50..1e3
dim_point_range[7] = 40..5e2
dim_point_range[8] = 30..25e1

# die Messergebnisse werden in eine Datei geschrieben die mit gnuplot gezeichnet wird
f = File.open('measurement.dat', 'w')

for dim in dim_range

    points = dim_point_range[dim].begin
    
    f.puts "# #{dim}D (index #{dim-2})\n# X Y\n"
    
    # Der Bereich wird durch 10 Geteilt und dieser Wert als Schrittweite verwendet.
    # Wir erhalten so 11 Messungen. 
    step = (dim_point_range[dim].end - dim_point_range[dim].begin) / 10;

    while points <= dim_point_range[dim].end

        print "calculating convex hull of #{points} points in #{dim}-D\n"
        output = IO.popen "rbox #{points} D#{dim} | qhull"

        # Messergebnis per regulären Ausdruck holen
        m = /CPU seconds to compute hull \(after input\): (.+)/.match output.read
        
        f.puts points.to_s + ' ' + m[1]
        
        points += step
    
    end
    # zwei neue Zeilen signalisieren eine neue Linie im File.
    f.puts "\n\n"
end

f.close

# Jetzt plotten wir die Ergebnisse mit gnuplot. Dazu wird ein eigenes Skript aufgerufen, das auch separat ausgeführt werden kann.
`./plot.rb`
