set terminal pngcairo enhanced size 800,800
set output 'figures/Q2-3d.png'
set pm3d
set palette defined (-3 "blue", 0 "white", 1 "red")
splot "data/Q2_temps_best.dat" matrix with lines notitle
