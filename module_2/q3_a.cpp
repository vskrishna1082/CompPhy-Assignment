#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

long double inv_func(long double x) {
    return -log(1-2*x);
}

int main()
{
    const int n_points = 10000;
    default_random_engine e;
    uniform_real_distribution<long double> u(0,0.5);

    ofstream exp_file;
    exp_file.open("exp_rand_nos.dat");
    for (int i=0; i<n_points; i++) {
        exp_file << setprecision(10) << inv_func(u(e))
            << "\n";
    }
    exp_file.close();
    return 0;
}
