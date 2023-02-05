set terminal pngcairo enhanced size 800,800
set output 'plots/q2_c_correlation.png'

set xlabel "Lag"
set ylabel "Auto-Correlation"
set xrange [-100:35000]
set size square
set style data dots
unset key

set title "Auto Correlation function"
plot "q_2_c_auto_correlation.dat" using 1 with lines
