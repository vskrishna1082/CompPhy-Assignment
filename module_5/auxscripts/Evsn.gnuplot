set terminal pngcairo enhanced size 500,400
set output 'figures/Evsn.png'

set xlabel "Basis Size (n)"
set ylabel "Bound-State Energy"
set xrange [0:50]
set style line 1 lc rgb '#000000' lt 2 lw 1 pt 6 pi -1 ps 1.5
unset key

set title "Energy vs n (a = 30)"
plot "data/Evsn.dat" with linespoints ls 1
