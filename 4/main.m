%% Praktikum 4 Linear Programming

close all;

% read data from file
fp = fopen('polygon.txt', 'r+');
P = fscanf( fp, '%f %f', [2 inf] );
P = P';
fclose( fp );

% draw polygon
figure, fill( P(:, 1), P(:,2), 'r' );

% calculate orientation of polygon

c = P(1:3,1:2);
c = horzcat(c, [1;1;1]);
ccwv = det(c);



