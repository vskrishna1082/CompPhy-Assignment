#include "q4_imp_sampling.h"
#include <iostream>
#include <cmath>
#include <random>
using namespace std;
/* importance sampling with approximate function as just exp */

double sq(double x) {
    return pow(x,2);
}

double func(double x_1,double x_2,double x_3,double y_1,double y_2,double y_3) {
    return exp(-sq(x_1) - sq(x_2) - sq(x_3) - sq(y_1) - sq(y_2) - sq(y_3) - 0.5*(sq(x_1 - y_1) + sq(x_2 - y_2) + sq(x_3 - y_3)));
}

double func(double x_1,double x_2,double x_3,double y_1,double y_2,double y_3) {
    return exp(-sq(x_1) - sq(x_2) - sq(x_3) - sq(y_1) - sq(y_2) - sq(y_3) ));
}

double eval_rand_pt(int seed)
{
    /* generate 6 random variables */
    mt19937 x_1(seed+1), x_2(seed+2), x_3(seed+3), y_1(seed+4), y_2(seed+5), y_3(seed+6);
    uniform_real_distribution<double> u(-2,2);
    double sum = 0;
    for (int i=0; i < n_i; i++) {
        sum += func(u(x_1),u(x_2),u(x_3),u(y_1),u(y_2),u(y_3));
    }
    double average = sum/n_i;
    double integral = average * pow(4,6);
    return integral;
}

