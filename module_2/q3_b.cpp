#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

double sigma=2;

double radial(double x) {
    return sigma*sqrt(-2*log(x)); // def only for x in (0,1]
}

double polar(double y) {
    return 2*M_PI*y*sigma;
}

double xy[2];
double *cartesian(double r, double theta)
{
    xy[0] = r*cos(theta);
    xy[1] = r*sin(theta);
    return xy;
}

int main()
{
    const int num_rand_nos = 10000;
    mt19937 x(3),y(4);
    uniform_real_distribution<double> u(0,1);

    ofstream x_file,y_file;
    x_file.open("gaussian_rv_3.dat");
    y_file.open("gaussian_rv_4.dat");
    for (int i=0; i<num_rand_nos; i++)
    {
        double gaussian[2];
        gaussian[0] = cartesian(radial(u(x)),polar(u(y)))[0];
        gaussian[1] = cartesian(radial(u(x)),polar(u(y)))[1];
        x_file << setprecision(10) << gaussian[0] << "\n";
        y_file << setprecision(10) << gaussian[1] << "\n";
    }
    x_file.close();
    y_file.close();
    return 0;
}
