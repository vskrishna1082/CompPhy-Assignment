#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main() {
    ofstream datafile;
    default_random_engine e(2);
    uniform_real_distribution<double> u(0,1);
    const int count=10;
    double sum=0;
    double average;

    datafile.open("test_ran.dat",ios::app);
    datafile << "\n# NOW calculating average of 10 random numbers\n";
    for (size_t i=0; i<count; i++) {
        sum += u(e);
    }
    average = sum / count;
    datafile << average << "\n";
    datafile.close();
    return 0;
}
