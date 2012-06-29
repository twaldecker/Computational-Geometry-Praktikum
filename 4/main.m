%% Praktikum 4 Linear Programming

close all;

% Daten in Matrix P einlesen
fp = fopen('polygon.txt', 'r+');
P = fscanf( fp, '%f %f', [2 inf] );
fclose( fp );

% Polygon zeichnen
figure, fill( P( 1, : ), P( 2, : ), 'r' );
hold on;

% Orientierung des Polygons berechnen
c = P(1:2,1:3)';
c = horzcat(c, [1;1;1]);
ccw = det(c);

% Berechnung der Normaleneinheitsvektoren
N = zeros( 2, size( P, 2 ) );
for i = 1:( size( P, 2 ) - 1 )
    N( :, i ) = vec1norm( P( :, i ), P( :, i+1 ), ccw );
end
N( :, size( P, 2 ) ) = vec1norm( P( :, size( P, 2 ) ), P( :, 1 ), ccw );

% linprog Komponenten berechnen
A = -1 .* N';
A( :, 3 ) = 1;

b = zeros( size( P, 2 ), 1 );
for i = 1:size( P, 2 )
    b( i ) = - P( 1, i ) * N( 1, i ) - P( 2, i ) * N( 2, i );
end

f = [ 0; 0; -1];

x =  linprog( f, A, b );

% Kreis zeichnen
phi = 0:0.05:2*pi;
xk = ( x( 3 ) * cos( phi ) ) + x( 1 );
yk = ( x( 3 ) * sin( phi ) ) + x( 2 );
plot( xk, yk, 'g' );
% Mittelpunkt zeichnen
plot( x( 1 ), x( 2 ), 'gx' );