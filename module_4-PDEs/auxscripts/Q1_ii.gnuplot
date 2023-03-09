set terminal pngcairo enhanced size 800,800
set output 'figures/Q1_ii-3d.png'
set pm3d
set view 60,45
set palette defined (-3 "blue", 0 "white", 1 "red")
set zlabel "Temperature" rotate parallel
set xlabel "X"
set ylabel "Y"
splot "data/Q1_ii_temps_best.dat" matrix with lines notitle
