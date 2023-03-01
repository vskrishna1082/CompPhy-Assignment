/* Solving Differential Equations with Gauss Seidel Method */

#include <iostream>
#include <fstream>
#include <array>
#include <cmath>
using namespace std;

const double dx = 0.01;
const double x_begin = 0, x_end = 1;

// solving $x_end = x_begin + (N-1)dx$ for N
const int N = (x_end - x_begin)/dx + 1;

// coefficients for y expression
const double a_0 = 1 / (2 - 10*dx*dx);
const double a_1 = 1 - 2.5*dx;
const double a_2 = 1 + 2.5*dx;
const double a_3 = 10*dx*dx;


struct point {
    double y_xmh;
    double y_xph;
    double x;
};

double update_y(struct point p) {
    return a_0*(a_1*p.y_xph + a_2*p.y_xmh - a_3*p.x);
}

int main()
{
    /* Create the initial guess array */
    array<double, N> y_init_array, y_curr, y_old, x_array;
    for (int i=0; i < y_init_array.size(); i++) {
        y_init_array[i] = 2*i*dx;
        x_array[i] = i*dx;
    }

    y_old = y_init_array;
    y_curr = y_init_array;

    int count = 0;
    bool Continue = true;
    while (Continue) {
        count += 1;
        Continue = false;
        y_old = y_curr;
        for (int i=1; i<N-1; i++) {
            struct point p = {y_curr[i-1],y_old[i+1],x_array[i]};
            y_curr[i] = update_y(p);

            if (abs(y_curr[i]-y_old[i]) > 0.0001) {
                Continue = true;
            }
        }
    }

    ofstream outfile;
    outfile.open("data/Q9_y_best.dat");
    for (int i=0; i<N; i++) {
        outfile << y_curr[i] << "\n";
    }
    outfile.close();

    cout << "Fit converged after " << count << " Iterations.\n";
    return 0;
}
