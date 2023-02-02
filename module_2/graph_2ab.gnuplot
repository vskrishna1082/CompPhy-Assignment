set terminal pngcairo enhanced size 800,400
set output 'plots/q2_ab.png'
set multiplot layout 1,2 scale 1,1

set style fill solid 1 border
set ylabel "Frequency"
set xlabel "Value"
set xrange [0:1]
binwidth=0.05
set boxwidth binwidth
set title "100000 Uniform Random Numbers"
set label "Bin Size = 0.05" at 0.6,55000
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'uniform_rand_0_1.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes

unset xrange
set title "Scatter Plot of 10000 numbers"
set xlabel "Index"
set ylabel "Value"
unset style
set style data dots
plot 'uniform_rand_0_1.dat' every ::0::10000 using 1

unset multiplot

