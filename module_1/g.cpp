#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
using namespace std;

/* calculate absolute difference between average of random
 * numbers and double 0.5 - with optional print statement*/
double randomMeanDiff(int count, bool print=false)
{
    default_random_engine e(2); // seed=1 produces too good an average at 10000
    uniform_real_distribution<double> u(0,1);
    double sum = 0;
    double average;
    double absDiff;
    const double trueMean = 0.50;

    // add `count` random numbers and calculate average
    for (size_t i=0; i<count; i++) {
        sum += u(e);
    }
    average = sum / count;
    absDiff = abs(trueMean - average);

    // print count : absolute_difference if print is set to true
    if (print == true) {
        cout << left << setw(10) << count << ":" << " " << \
            setprecision(10) << absDiff << "\n";
    }
    return absDiff;
}

int main() {
    cout << "Absolute difference between 0.5 and average of "
        "random numbers\n";
    randomMeanDiff(10,true);
    randomMeanDiff(100,true);
    randomMeanDiff(10000,true);
    randomMeanDiff(1000000,true);
    cout << "The difference converges to 0.5 with increasing number of random numbers\n"
        "This is expected as the expectation value of a uniform random vairable in interval (0,1) is 0.5\n";
    return 0;
}
