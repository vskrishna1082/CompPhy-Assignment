set terminal pngcairo enhanced size 800,800
set output 'plots/q4_brute.png'

set style fill solid 1 border
set ylabel "Frequency"
set xlabel "Integrand"
binwidth=0.1
set boxwidth binwidth
set title "Mone Carlo Brute-Force Integration"
bin(x,width)=width*floor(x/width)+width/2.0
unset key
plot 'Brute_Monte_Carlo.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes
