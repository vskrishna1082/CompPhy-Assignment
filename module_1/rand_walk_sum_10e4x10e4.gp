set terminal png size 900,400
set output 'plots/random_walk_sum_10e4x10e4_bins.png'
set multiplot layout 1, 2 scale 1,1 # title "Distribution of sum of random numbers"
set style fill solid 1 border
set xtics -400,200,400
set xrange [-900:900]
set yrange [0:0.01]
set ylabel "Probablity Density"
set xlabel "Sum"
set size square
#
binwidth=2
set boxwidth binwidth
set title "Bin Size = 2"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_walk_sums.dat' using (bin($1,binwidth)):(1.0) smooth fnormal with boxes
#
binwidth=5
set boxwidth binwidth
set title "Bin Size = 5"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_walk_sums.dat' using (bin($1,binwidth)):(1.0) smooth fnormal with boxes
#
binwidth=10
set boxwidth binwidth
set title "Bin Size = 10"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_walk_sums.dat' using (bin($1,binwidth)):(1.0) smooth fnormal with boxes
