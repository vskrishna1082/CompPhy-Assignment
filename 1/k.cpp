#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <iterator>
#include <random>
using namespace std;

int sumRandomWalk(int seed = 1)
{
    int intList[2] = {-1,1};
    int intArray[10000];
    default_random_engine e(seed);
    uniform_int_distribution<> u(0,1);
    int sum=0;
    for (int i=0; i<10000; i++) {
        sum+=intList[u(e)];
    }
    return sum;
}
int main()
{
    array<double, 100000> sums;
    ofstream datafile;
    datafile.open("random_walk_sums_10E5x10E4.dat");

    int i =0;
    // parallelize using openmpp (g++: compile with -fopenmp flag)
    #pragma omp parallel for
        for (auto it = begin(sums); it != end(sums); ++it)
        {
            *it = sumRandomWalk(i+1); // set i_th element of array
            ++i;
        }
    sort(sums.begin(), sums.end()); // sort the array for binning

    /* Uncomment the following two lines to print all elements of array*/
    copy(sums.begin(), sums.end(), ostream_iterator<int>(datafile, "\n"));
    datafile.close();
    return 0;
}
