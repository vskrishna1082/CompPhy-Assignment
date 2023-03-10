/* Solve a first order IVP using Runge-Kutta RK4 method */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double y_actual = 48.0784824792;

double derivative_func(auto x, auto y) {
    return pow(y,2)+1;
}

int main()
{
    double curr_x = 0;
    double dx = 0.01;
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

        double y1 = curr_y + slope1*(0.5*dx); //temporary y
        double slope2 = derivative_func(curr_x+0.5*dx,y1);

        double y2 = curr_y + slope2*(0.5*dx);
        double slope3 = derivative_func(curr_x+0.5*dx,y2);

        double y3 = curr_y + slope3*(dx);
        double slope4 = derivative_func(curr_x+dx,y3);

        double slope = (1.0/6.0)*(slope1+slope4+2*(slope2+slope3));
        double next_fx = curr_y + slope*(dx);
        sol_vector.push_back(next_fx);
        curr_x += dx;
    }
    cout << curr_x << endl;
    cout << abs(y_actual - sol_vector.back()) << endl;
    return 0;
}
