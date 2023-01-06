#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main()
{
    ofstream myfile;
    default_random_engine e;
    uniform_real_distribution<double> u(0,1);

    e.seed(2); // default seed is 1
    myfile.open("test_ran.dat", ios::app);
    for (int i=0;i<10;i++) {
        myfile << u(e) << "\n";
    }
    myfile.close();
    return 0;
}

