/* Solve a first order IVP using modified Euler's method */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double y_actual = 48.078;

/* estimate the function at x+dx, given value at x 
 * and derivative of function - modified to use 
 * slope at x+dx/2*/
double est_func_dx(double (*func_derivative)(double, double), double x, double f_at_x, double fx_slope, double dx) {
    return f_at_x + func_derivative(x, fx_slope)*dx; // first order taylor expansion
}

double derivative_func(auto x, auto y) {
    return pow(y,2)+1;
}

int main()
{
    double curr_x = 0;
    double dx = 0.001;
    cout << "Enter Step Size:" << endl;
    cin >> dx; 
    vector<double> sol_vector = {};

    double init_fx = 0;
    sol_vector.push_back(init_fx);

    /* checking if x is dx away from 1.55 should work but
     * it doesn't catch 1.549 for dx = 0.001 */
    while (curr_x+0.5*dx <= 1.55)
    {
        double curr_y = sol_vector.back();
        double mid_fx = est_func_dx(&derivative_func, curr_x, curr_y, curr_y, dx/2);
        double next_fx = est_func_dx(&derivative_func, curr_x, curr_y, mid_fx, dx);
        sol_vector.push_back(next_fx);
        curr_x += dx;
    }
    cout << abs(y_actual -sol_vector.back()) << endl;
    return 0;
}
