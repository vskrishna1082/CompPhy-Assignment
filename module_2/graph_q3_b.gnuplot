set terminal pngcairo enhanced size 800,400
set output 'plots/q3_b_gaussians.png'
set multiplot layout 1,3 scale 1,1

set xlabel "Variable 1"
set ylabel "Variable 2"
set size square
set style data dots
unset key

set title "Scatter Plot of Gaussian Vars"
plot "<paste gaussian_rv_1.dat gaussian_rv_2.dat" using 1:2

set style fill solid 1 border
set ylabel "Frequency"
set xlabel "Value"
binwidth=0.1
set boxwidth binwidth
set title "Gaussian Variable 1"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'gaussian_rv_1.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes

set title "Gaussian Variable 2"
unset key
plot 'gaussian_rv_2.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes

unset multiplot
