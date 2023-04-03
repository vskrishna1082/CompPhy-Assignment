#! /bin/bash
# Increments value of 'n' from 5 to 50, recompiles and runs Q1_b.cpp

set -e

# get initial value of n
cur_n=$(grep -oP '(?<=n\=)(\d+)' Q1_b.cpp)
old_n=$cur_n
init_n=$cur_n
echo
echo Found initial n value: $init_n
echo Clearing Evsn.dat
rm data/Evsn.dat && touch data/Evsn.dat

while (($cur_n<55)); do
    sed -i "s/n=$old_n/n=$cur_n/g" ./Q1_b.cpp
    echo Running for n=$cur_n
    g++ Q1_b.cpp -o Q1_b.out -O3 $(pkg-config --cflags eigen3) && ./Q1_b.out >> data/Evsn.dat
    old_n=$cur_n
    cur_n=$(($cur_n+5))
done

echo Resetting n
sed -i "s/n=$old_n/n=$init_n/g" ./Q1_b.cpp
echo Done!
