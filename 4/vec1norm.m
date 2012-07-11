%% Funktion zur Berechnung der Normaleneinheitsvektoren
function [ n ] = vec1norm( a, b, dir )
    % Berechnung des Richtungsvektors
    v = b - a;
    % Berechnung des Normalenvektors (Richtung abhängig von dir)
    if( dir > 0 )
        n = [ -v(2); v(1) ];
    else
        n = [ v(2); -v(1) ];
    end
    % Normierung des Normalenvektors
    n = n ./ norm( n, 2 );
end