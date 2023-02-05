#include <cmath>
using namespace std;
double sigma = sqrt(0.5);

double gauss_rand(double uniformRandNo1, double uniformRandNo2) {
    double &urand1 = uniformRandNo1;
    double &urand2 = uniformRandNo2;
    double radial = sigma*sqrt(-2*log(urand1));
    double polar = 2*M_PI*sigma*urand2;
    double gauss_rand_no[0] = radial*cos(polar); 
    double gauss_rand_no[1] = radial*sin(polar); 
    return gauss_rand_no;
}
