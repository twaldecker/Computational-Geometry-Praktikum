%% Praktikum 4 Linear Programming

close all;

% read data from file
fp = fopen('testpolygon.txt', 'r+');
P = fscanf( fp, '%f %f', [2 inf] );
P = P';
fclose( fp );

% draw polygon
figure, fill( P(:, 1), P(:,2), 'r' );