set terminal pngcairo enhanced size 800,600
set output 'figures/Evsa.png'

set xlabel "Periodicity (a)"
set ylabel "Bound-State Energy"
set xrange [0:30]
set style line 1 lc rgb '#000000' lt 1 lw 1 pt 6 pi -1 ps 1.5
unset key

set title "Energy vs a (n = 50)"
plot "data/Evsa.dat" with linespoints ls 1
