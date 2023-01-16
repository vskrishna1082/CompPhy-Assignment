#include <iostream>
#include <fstream>
#include <random>
using namespace std;

void randomAverage(int count) // appends average of <count> random numbers to test_ran.dat
{
    ofstream datafile;
    default_random_engine e(2); // seed=1 produces too good an average at 10000
    uniform_real_distribution<double> u(0,1);
    double sum = 0;
    double average;

    datafile.open("test_ran.dat", ios::app);
    datafile << "\n# Now calculating average of " << count << " random numbers\n";
    for (size_t i=0; i<count; i++) {
        sum += u(e);
    }
    average = sum / count;
    datafile << average << "\n";
    datafile.close();
}

int main()
{
    randomAverage(100);
    randomAverage(10000);
    randomAverage(1000000);
    return 0;
}
