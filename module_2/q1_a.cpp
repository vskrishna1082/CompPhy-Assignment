/* integration of 1/(1+x^2) using trapezoidal integration */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "trap_integrator.h"
using namespace std;

const double pi=M_PI;
bool verbose = true;

/* return the value of the function at x */
double func(double x) {
    return 4/(1+pow(x,2));
}

long binner(long i)
{
    long bins = i;
    if (verbose == true) {
        bins = pow(10,i+2);
    }
    return bins;
}

int main()
{
    long iterations= 10000;

    if (verbose == true) {
        iterations= 4;
    }

    double log_bins_array[iterations];
    double pi_estimate, pi_error, log_pi_errors[iterations];

    for (long i=0; i<iterations; i++)
    {
        long n_bins = binner(i);
        pi_estimate = trap_integrate(n_bins,0,1, &func); // estimate pi with n_bins
        pi_error = abs(pi - pi_estimate);

        log_pi_errors[i] = log10(pi_error); // add log of error in array
        log_bins_array[i] = log10(n_bins); // add log of binsize in array
    }

    ofstream x_axis_file;
    ofstream y_axis_file;
    x_axis_file.open("q1_a_x.dat");
    y_axis_file.open("q1_a_y.dat");

    for (long i=0; i<iterations; i++) {
        x_axis_file << log_bins_array[i] << "\n";
        y_axis_file << setprecision(12) << log_pi_errors[i] << "\n";
    }

    if (verbose == true) {
        for (long i=0; i<iterations; i++) {
            cout << setw(6) << left << log_bins_array[i] << ":" << setprecision(15) << log_pi_errors[i] << "\n";
        }
    }

    x_axis_file.close();
    y_axis_file.close();
    return 0;
}
