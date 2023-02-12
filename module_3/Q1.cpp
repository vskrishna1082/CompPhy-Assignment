/* Solve a first order IVP using Euler's method */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double y_actual = 48.078;

/* estimate the function at x+dx, given value at x 
 * and derivative of function */
double est_func_dx(double (*func_derivative)(double, double), double x, double f_at_x, double dx) {
    return f_at_x + func_derivative(x, f_at_x)*dx; // first order taylor expansion
}

double derivative_func(auto x, auto y) {
    return pow(y,2)+1;
}

int main()
{
    double curr_x = 0;
    double dx = 0.01;
    vector<double> sol_vector = {};

    double init_fx = 0;
    sol_vector.push_back(init_fx);

    while (curr_x < 1.55)
    {
        double next_fx = est_func_dx(&derivative_func, curr_x, sol_vector.back(), dx);
        sol_vector.push_back(next_fx);
        curr_x += dx;
    }
    cout << abs(y_actual -sol_vector.back()) << endl;
    return 0;
}
