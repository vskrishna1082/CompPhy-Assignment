#include <cmath>
#include <array>
using namespace std;
double sigma = sqrt(0.5);

array<double, 2> gauss_rand(double uniformRandNo1, double uniformRandNo2) {
    double &urand1 = uniformRandNo1;
    double &urand2 = uniformRandNo2;
    double radial = sigma*sqrt(-2*log(urand1));
    double polar = 2*M_PI*urand2;
    array<double,2> gauss_rand_no;
    gauss_rand_no[0] = radial*cos(polar); 
    gauss_rand_no[1] = radial*sin(polar); 
    return gauss_rand_no;
}
