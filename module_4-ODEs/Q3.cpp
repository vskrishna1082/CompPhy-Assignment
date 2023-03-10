/* Solve a first order IVP using improved Euler's method */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double y_actual = 48.078;

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
        double slope1 = derivative_func(curr_x,curr_y);
        double end_y = curr_y + slope1*(dx); /* estimated y at x+dx */
        double slope2 = derivative_func(curr_x+dx,end_y);
        double slope = 0.5*(slope1 + slope2);
        double next_fx = curr_y + slope*(dx);
        sol_vector.push_back(next_fx);
        curr_x += dx;
    }
    cout << abs(y_actual -sol_vector.back()) << endl;
    return 0;
}
