%% load data

diff = load('diff.dat');
base = load('strecken/test5.dat');


%% loop and plot always two lines

figure, hold on;

for i = 1:length(base)
  plot([base(i,1), base(i,3)], [base(i,2), base(i,4)])
end

for i = 1:length(diff)
  plot([diff(i,1), diff(i,3)], [diff(i,2), diff(i,4)], 'r-')
end
%%
slint = load('SLIntersections.dat');
plot(slint(:,1)', slint(:,2)', 'g+')

%%
figure, hold on;
test = load('strecken/test5.dat');
for i = 1:length(test)
  plot([test(i,1), test(i,3)], [test(i,2), test(i,4)])
end
