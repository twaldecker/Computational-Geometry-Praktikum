%% Praktikum 4 Linear Programming

close all;

% Daten einlesen
fp = fopen('testpolygon.txt', 'r+');
P = fscanf( fp, '%f %f', [2 inf] );
fclose( fp );

% Polygon zeichnen
figure, fill( P( 1, : ), P( 2, : ), 'r' );

% Orientierung des Polygons berechnen
c = P(1:2,1:3)';
c = horzcat(c, [1;1;1]);
ccw = det(c);

% Berechnung der Normaleneinheitsvektoren
N = zeros( 2, size( P, 2 ) );
for i = 1:( size( P, 2 ) - 1 )
    N( :, i ) = vec1norm( P( :, i ), P( :, i+1 ), ccw );
end
N( :, size( P, 2) ) = vec1norm( P( :, end ), P( :, 1 ), ccw );

