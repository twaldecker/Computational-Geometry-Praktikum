#!/bin/env ruby
# encoding: utf-8

fileb = "intersection.dat"
filea = "sweepline.dat"

# create a multidimensional array of file b:
b = []
File.open(fileb, 'r') do |file|
  file.each_line do |line|
    b << line.split(" ") # split at spaces
  end
end

# now read a line from a and search it in the b array.
# if we find it in b, we delete it.
# if we don't find it we save it in another array.

# open the two output files
File.open(filea, 'r') do |file|
  file.each_line do |line|
    a = line.split(" ") # split at spaces
    
    b.delete_if do |s| 
      s.include?(a[0]) &&
      s.include?(a[1]) &&
      s.include?(a[2]) &&
      s.include?(a[3]) &&
      s.include?(a[4]) &&
      s.include?(a[5]) &&
      s.include?(a[6]) &&
      s.include?(a[7])
    end
      
  end
end

b.each do |i|
  puts i[0] +" "+ i[1] + " " + i[2] + " " + i[3] + "\n" + i[4] + " " + i[5] + " " + i[6] + " " + i[7]
end

$stderr.puts b.count
