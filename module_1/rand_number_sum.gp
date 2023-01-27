set terminal png size 900,400
set output 'plots/random_numbers_sum.png'
set multiplot layout 1, 3 scale 1,1 # title "Distribution of sum of random numbers"
set style fill solid 1 border
set ylabel "Frequency"
set xlabel "Sum"
set xrange [4900:5100]
set xtics 4850,50,5100 out
set size square
#
binwidth=0.5
set boxwidth binwidth
set title "Bin Size = 0.5"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_numbers_sums.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes
#
binwidth=1
set boxwidth binwidth
set title "Bin Size = 1"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_numbers_sums.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes
#
binwidth=2
set boxwidth binwidth
set title "Bin Size = 2"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'random_numbers_sums.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes
#
unset multiplot
