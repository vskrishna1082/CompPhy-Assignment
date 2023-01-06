#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main()
{
    ofstream myfile;
    default_random_engine e;
    uniform_real_distribution<double> u(0,1);

    myfile.open("test_ran.dat", ios::app); // open in append mode
    myfile << "\n# Changing seed and generating 10 new random numbers\n\n";
    myfile.close();
    return 0;
}
