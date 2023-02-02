set terminal pngcairo enhanced size 800,400
set output 'plots/q3_a_exponential.png'
set multiplot layout 1,2 scale 1,1

set xlabel "Variable 1"
set ylabel "Variable 2"
set size square
set style data dots
unset key

set title "Scatter Plot of Exponential Vars"
plot "exp_rand_nos.dat" using 1

set style fill solid 1 border
set ylabel "Frequency"
set xlabel "Value"
binwidth=0.1
set boxwidth binwidth
set title "Exponential Variable"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'exp_rand_nos.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes

unset multiplot

