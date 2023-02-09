#include "q4_imp_sampling.h"
#include <iostream>
#include <cmath>
#include <random>
#include <iterator>
#include <fstream>
using namespace std;
/* importance sampling with approximate function as just exp */

const int n_i = 10000;
array<double, n_i> integrals;

double sq(double x) {
    return pow(x,2);
}

double new_func(double x_1,double x_2,double x_3,double y_1,double y_2,double y_3) {
    return exp(-0.5*(sq(x_1-y_1) + sq(x_2-y_2) + sq(x_3-y_3)));
}

double eval_rand_pt(int seed)
{
    /* generate 6 random variables */
    mt19937 x_1(seed+1), x_2(seed+2), x_3(seed+3), y_1(seed+4), y_2(seed+5), y_3(seed+6);
    uniform_real_distribution<double> u(0,1);
    double sum = 0;
    for (int i=0; i < n_i; i++)
    {
        double x1 = gauss_rand(u(x_1),u(y_1))[0];
        double y1 = gauss_rand(u(x_1),u(y_1))[1];
        double x2 = gauss_rand(u(x_2),u(y_2))[0];
        double y2 = gauss_rand(u(x_2),u(y_2))[1];
        double x3 = gauss_rand(u(x_3),u(y_3))[0];
        double y3 = gauss_rand(u(x_3),u(y_3))[1];
        sum += new_func(x1,x2,x3,y1,y2,y3);
    }
    double integral = sum/n_i;
    return integral*pow(M_PI,3);
}

int main()
{
    ofstream outfile;
    outfile.open("Importanc_Sampling_MC.dat");
#pragma omp parallel for
    for (int i=0; i<n_i; i++) {
        double estimate = eval_rand_pt(i);
        integrals[i] = estimate;
    }
    copy(integrals.begin(), integrals.end(), ostream_iterator<double>(outfile, "\n"));
    outfile.close();
}
