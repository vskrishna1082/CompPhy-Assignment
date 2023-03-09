/* Neumann Boundary Condition problem */

#include <iostream>
#include <fstream>
#include <array>
#include <cmath>
#include <algorithm>
using namespace std;

template <typename T, size_t I, size_t J>
using TwoDArray = array<array<T, I>, J>;

int main()
{
    /* generate the array */
    TwoDArray<double,34,34> temps = {0}, temps_old = {0};
    int dx = 1;

    /* Initial conditions */
    double A = -70, B = -40, C = 20, D = -10;
    double temp_11 = 0;

    int count = 0;
    bool Continue = true;
    while (Continue) {
        count += 1;
        Continue = false;
        temps_old = temps;

        /* update the corner points */
        temps[0][0]   = 0.5*(temps_old[0][1] - dx*C + temps_old[1][0] - dx*A);
        temps[0][33]  = 0.5*(temps_old[0][32] + dx*D + temps_old[1][33] - dx*A);
        temps[33][0]  = 0.5*(temps_old[32][0] + dx*B + temps_old[33][1] - dx*C);
        temps[33][33] = 0.5*(temps_old[32][33] + dx*B + temps_old[33][32] + dx*D);

        /* update the borders (not corners)*/
        for (int x=1; x<33; x++) {
            temps[0][x] = 0.25*( 2*temps_old[1][x] +
                                 temps_old[0][x+1] +
                                 temps_old[0][x-1] -
                                 2*dx*A );
            temps[33][x] = 0.25*(2*temps_old[32][x] +
                                 temps_old[33][x+1] +
                                 temps_old[33][x-1] +
                                 2*dx*B );
            temps[x][0] = 0.25*( 2*temps_old[x][1] +
                                 temps_old[x+1][0] +
                                 temps_old[x-1][0] -
                                 2*dx*C );
            temps[x][33] = 0.25*(2*temps_old[x][32] +
                                 temps_old[x+1][33] +
                                 temps_old[x-1][33] +
                                 2*dx*D );

        /* update interior */
            for (int y = 1; y<33; y++) {
               temps[x][y] = 0.25*(temps_old[x-1][y] +
                                   temps_old[x+1][y] +
                                   temps_old[x][y-1] +
                                   temps_old[x][y+1]);

            }
        }
        for (int x = 0; x<34; x++) {
            for (int y = 0; y < 34; y++) {
               if (abs(temps_old[x][y]-temps[x][y]) > 0.00001) {
                   Continue = true;
                   /* cout << "fail_margin:" << abs(temps_old[x][y]-temps[x][y]) << "\n"; */
               }
           }
        }
    }

    ofstream outfile;
    outfile.open("data/Q2_temps_best.dat");
    double shift_temp = 2000 - temps[0][0];
    for (int i=0; i<34; i++) {
        for (int j=0; j<34; j++) {
            outfile  << " " << temps[j][i];
        }
        outfile << "\n";
    }
    outfile.close();
    cout << "Fit converged after " << count << " Iterations.\n";
    cout << temps[9][9] + shift_temp << "\n";
}
