#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main()
{
    ofstream myfile; // open file for output
    default_random_engine e;
    uniform_real_distribution<double> u(0,1);

    myfile.open("test_ran.dat");
    for (int i=0;i<10;i++) {
        myfile << u(e) << endl;
    }
    myfile.close();
    return 0;
}

