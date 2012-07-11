%% Praktikum 4 Linear Programming

%% Workspace aufräumen
clear all;
close all;

%% Daten in Matrix P einlesen
fp = fopen('polygon.txt', 'r+');
P = fscanf( fp, '%f %f', [2 inf] );
fclose( fp );

%% Polygon zeichnen
figure, fill( P( 1, : ), P( 2, : ), 'b' );
axis equal;
hold on;

%% Orientierung des Polygons berechnenen
%  - konvexes Polygon wird vorrausgesetzt
%  - Berechnung des ccw-Werts mittels Determinante der ersten drei Punkte
c = P(1:2,1:3)';
c = horzcat(c, [1;1;1]);
ccw = det(c);

%% Berechnung der Normaleneinheitsvektoren pro Polygonabschnitt
%  - durch Übergabe des ccw-Werts zeigt der Normaleneinheitsvektor ins
%    Innere des Polygons (siehe vec1norm Funktion)
N = zeros( 2, size( P, 2 ) );
for i = 1:( size( P, 2 ) - 1 )
    N( :, i ) = vec1norm( P( :, i ), P( :, i+1 ), ccw );
end
N( :, size( P, 2 ) ) = vec1norm( P( :, size( P, 2 ) ), P( :, 1 ), ccw );

%% linprog Komponenten berechnen
%  lineares Programm hat die mathematische Form:
%  b1 >= a11*x1 + a12*x2 + ... a1n*xn
%  .
%  .
%  .
%  bm >= am1*x1 + am2*x2 + ... amn*xn

%  Auf den Ansatz d*n >= r mit d = m - a übertragen erhält man:
%  - a1*n1 - a2*n2 >= - n1*m1 - n2*m2 + r
%  .
%  .
%  .
%  damit folgt:
%  Matrix A entspricht der negierten Transponierten von N
A = -1 .* N';
%  Radius immer 1
A( :, 3 ) = 1;
%  Vektor b (siehe oben)
b = zeros( size( P, 2 ), 1 );
for i = 1:size( P, 2 )
    b( i ) = - P( 1, i ) * N( 1, i ) - P( 2, i ) * N( 2, i );
end
%  Ziel ist ein maximaler Radius --> -r minimieren
%  Zielfunktion
f = [ 0; 0; -1];
%  Lösung berechnen
x =  linprog( f, A, b );

%% Ergebnis zeichnen
%  Kreis
phi = 0:0.05:2*pi;
xk = ( x( 3 ) * cos( phi ) ) + x( 1 );
yk = ( x( 3 ) * sin( phi ) ) + x( 2 );
plot( xk, yk, 'r' );
%  Mittelpunkt
plot( x( 1 ), x( 2 ), 'rx' );