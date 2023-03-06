/* Motion of particles on a circular ring - SHM */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

const int n_particles = 50;

struct state {
    array<vector<double>, n_particles> y; 
    array<vector<double>, n_particles> v; 
    double t;
};

double dvdt_func(struct state state, int i)
{
    double y_i = state.y[i].back();
    double y_im1, y_ip1;
    if (i == 0) {
        y_im1 = state.y.back().back(); /* latest y value of last particle */
        y_ip1 = state.y[i+1].back();
    }
    else if (i == n_particles - 1) {
        y_im1 =  state.y[i-1].back();
        y_ip1 = state.y[0].back();
    }
    else {
        y_ip1 =  state.y[i+1].back();
        y_im1 =  state.y[i-1].back();
    }
    return y_ip1 + y_im1 -2*y_i;
}

struct state rk_increment(struct state curr_state, double dt)
{
    const double dtby2 = 0.5*dt;
    array<double, n_particles> slope1 = {0}, slope2 = {0}, slope3 = {0}, slope4 = {0};
    struct state int_state1, int_state2, int_state3, ret_state;

    /* First Intermediate point */
    for (int i = 0; i < n_particles; i++) {
        double y0 = curr_state.y[i].back();
        double v0 = curr_state.v[i].back();
        double slope1_i = dvdt_func(curr_state, i);
        slope1[i] = slope1_i;
        int_state1.v[i].push_back(v0 + slope1[i]*dtby2);
        int_state1.y[i].push_back(y0 + v0*dtby2);
    }

    /* Second Intermediate point */
    for (int i = 0; i < n_particles; i++) {
        const double& y0 = curr_state.y[i].back();
        const double& v0 = curr_state.v[i].back();
        const double& v1 = int_state1.v[i].back();
        slope2[i] = dvdt_func(int_state1, i);
        int_state2.v[i].push_back(v0 + slope2[i]*dtby2);
        int_state2.y[i].push_back(y0 + v1*dtby2);
    }
    
    /* Third Intermediate point */
    for (int i = 0; i < n_particles; i++) {
        double y0 = curr_state.y[i].back();
        double v0 = curr_state.v[i].back();
        double v2 = int_state2.v[i].back();
        slope3[i] = dvdt_func(int_state2, i);
        int_state3.v[i].push_back(v0 + slope2[i]*dt);
        int_state3.y[i].push_back(y0 + v2*dt);
    }

    for (int i = 0; i < n_particles; i++) {
        slope4[i] = dvdt_func(int_state3, i);
    }

    /* Return State */
    ret_state = curr_state;
    ret_state.t = curr_state.t+ dt;
    for (int i = 0; i < n_particles; i++) {
        double slope = (1.0/6.0)*(slope1[i] + slope4[i] + 2*(slope2[i] + slope3[i]));
        double v_as_slope = (1/6.0)*(
                curr_state.v[i].back() + 
                int_state3.v[i].back() + 
                2*(int_state2.v[i].back() + int_state1.v[i].back()));
        double y0 = curr_state.y[i].back();
        double v0 = curr_state.v[i].back();
        ret_state.y[i].push_back(y0 + v_as_slope*dt);
        ret_state.v[i].push_back(v0 + slope*dt);
    }
    return ret_state;
}

int main()
{
    double t_final = 40;
    double dt = 0.02;
    vector<double> init_vector = {0}; // set all values to 0
    struct state curr_state;

    /* intiialize y and v to init_vector */
    for (int i=0; i < n_particles; i++) {
        curr_state.y[i] = init_vector;
        curr_state.v[i] = init_vector;
    }

    /* intial conditions */
    curr_state.y[0][0]  = 0.8;
    curr_state.y[25][0] = 0.8;

    while (curr_state.t < t_final) {
        curr_state = rk_increment(curr_state, dt);
    }
    cout << curr_state.y[0].back() << endl;

    ofstream p1_posfile;
    p1_posfile.open("data/Q8_particle_1_pos.dat");
    for (int i = 0; i < curr_state.y[0].size(); i++) {
        p1_posfile << curr_state.y[0][i] << ","
            << curr_state.y[25][i] << "\n";
    }
    p1_posfile.close();

    /* const double norm = 2*M_PI/n_particles; */
    /* const double radius = 5; */
    /* array<ofstream, 1000> outfiles; */
    /* for (int i = 0; i < outfiles.size(); i++) { */
    /*     outfiles[i].open("position_at_"+to_string(2*i)); */
    /*     outfiles[i] << "50\n\n"; */
    /*     for (int j = 0; j < curr_state.y.size(); j++) { */
    /*         outfiles[i] << "N " << radius*cos(norm*j) << " " << radius*sin(norm*j) << " " << curr_state.y[j][2*i] << "\n"; */
    /*     } */
    /*     outfiles[i].close(); */
    /* } */
    return 0;
}
