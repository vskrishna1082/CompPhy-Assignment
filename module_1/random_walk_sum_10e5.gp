set terminal png size 850,400
set output 'plots/random_walk_sum_10e5_bins.png'
set multiplot layout 1, 2 scale 1,1 # title "Distribution of sum of random numbers"
set style fill solid 1 border
set xrange [-900:900]
set yrange [0:0.01]
set ylabel "Probablity Density"
set xlabel "Sum"
set size square
#
binwidth=2
set boxwidth binwidth
set title "100000 samples + 10000 random numbers"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_walk_sums_10E5x10E4.dat' using (bin($1,binwidth)):(0.5) smooth fnormal with boxes
#
set boxwidth binwidth
set xtics -800,400,800
set title "100000 samples + 100000 random numbers"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_walk_sums_10E5x10E5.dat' using (bin($1,binwidth)):(0.5) smooth fnormal with boxes
unset multiplot
