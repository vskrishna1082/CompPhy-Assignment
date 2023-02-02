set terminal pngcairo enhanced size 600,400
set output 'plots/3d_plot_q4.png'
unset key
set grid
set xrange [-3:3]
set yrange [-3:3]
set isosample 35
set ztics 0,0.5,1
set title '3D-plot of g(x,y)'
splot exp(-x**2 - y**2 - ((x-y)**2)/2)
