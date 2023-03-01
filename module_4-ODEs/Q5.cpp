/* Solve a second order IVP using Runge-Kutta RK4 method */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct xvt {
    double x;
    double v;
    double t;
};

double dvdt_func(struct xvt xvt) {
    return -1*sin(xvt.x);
}

struct xvt runge_kutta(
        double curr_x,
        double curr_v,
        double curr_t,
        double dt)
{
    struct xvt curr_xvt = { curr_x, curr_v, curr_t};
    double slope1 = dvdt_func(curr_xvt);
    double v1 = curr_v + slope1*(0.5*dt);
    double x1 = curr_x + curr_v*(0.5*dt);

    struct xvt int_pt1 = {x1, v1, curr_t + 0.5*dt};
    double slope2 = dvdt_func(int_pt1);
    double v2 = curr_v + slope2*(0.5*dt);
    double x2 = curr_x + v2*(0.5*dt);

    struct xvt int_pt2 = {x2, v2, curr_t + 0.5*dt};
    double slope3 = dvdt_func(int_pt2);
    double v3 = curr_v + slope3*(dt);
    double x3 = curr_x + v3*(dt);

    struct xvt int_pt3 = {x3, v3, curr_t+dt};
    double slope4 = dvdt_func(int_pt3);

    double slope = (1/(double)6)*(slope1+slope4+2*(slope2+slope3));
    double v_as_slope = (1/(double) 6)*(curr_v + v3 + 2*(v1 + v2)); 

    double next_x = curr_x + v_as_slope*dt;
    double next_v = curr_v + slope*dt;
    double next_t = curr_t + dt;
    struct xvt next_xvt = {next_x, next_v, next_t}; 
    return next_xvt;
}

int main()
{
    double curr_t = 0;
    double dt = 0.01;
    vector<double> x_vector = {};
    vector<double> v_vector = {};

    double init_x = 0.1;
    x_vector.push_back(init_x);
    double init_v = 1.9;
    v_vector.push_back(init_v);

    while (curr_t < 50)
    {
        double curr_x = x_vector.back();
        double curr_v = v_vector.back();
        struct xvt next_xvt = runge_kutta(curr_x, curr_v, curr_t, dt);
        x_vector.push_back(next_xvt.x);
        v_vector.push_back(next_xvt.v);
        curr_t += dt;
    }

    ofstream outfile;
    outfile.open("data/Q5.dat");
    for (int i=0; i<x_vector.size(); i++) {
        outfile << x_vector[i] << "," << v_vector[i] << "\n";
    }
    outfile.close();
    return 0;
}
