// calculate sum of 10000 random numbers 10000 times and bin them
#include <iostream>
#include <iomanip>
#include <fstream>
#include <array>
#include <algorithm>
#include <iterator>
#include <random>
using namespace std;

double sumRandom(int seed=1) // adds 10000 random numbers
{
    default_random_engine e(seed);
    uniform_real_distribution<double> u(0,1);
    double sum=0;
    for (int i=0; i<10000; i++) {
        sum+=u(e);
    }
    return sum;
}

int main()
{
    array<double, 10000> sums;
    ofstream datafile;
    datafile.open("random_numbers_sums.dat");
    int i =0;
    // parallelize using openmpp (g++: compile with -fopenmp flag)
    #pragma omp parallel for
        for (auto it = begin(sums); it != end(sums); ++it)
        {
            *it = sumRandom(i+10); // set i_th element of array
            ++i;
        }
    sort(sums.begin(), sums.end()); // sort the array for binning

    /* Uncomment the following two lines to print all elements of array*/
    copy(sums.begin(), sums.end(), ostream_iterator<double>(datafile << setprecision(2) << fixed, "\n"));
    datafile.close();

    return 0;
}
