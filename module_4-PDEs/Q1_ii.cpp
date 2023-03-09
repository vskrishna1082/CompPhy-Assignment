/* PDEs using finite difference method */

#include <iostream>
#include <fstream>
#include <array>
#include <cmath>
using namespace std;

template <typename T, size_t I, size_t J>
using TwoDArray = array<array<T, I>, J>;

int main()
{
    /* generate the array */
    TwoDArray<double,34,34> temps_init={0}, temps, temps_old;

    /* Initial conditions: T_a = 3.7, T_b = 0.4
     * For lerp: d = (b-a)/(n-1) = 0.1*/
    for (int i=0; i<34; i++) {
        temps_init[i][0] = 3.7; /* x in columns, y along rows*/
        temps_init[i][33] = 0.4;
        temps_init[0][i] = 3.7 - i*0.1; /* a + (n-1)*d */
        temps_init[33][i] = temps_init[0][i];
    }

    /* more conditions */
    temps_init[16][0] = 0.4;
    temps_init[17][0] = 0.4;
    temps_init[16][33] = 3.7;
    temps_init[17][33] = 3.7;

    temps = temps_init;
    temps_old = temps_init;

    int count = 0;
    bool Continue = true;
    while (Continue) {
        count += 1;
        Continue = false;
        temps_old = temps;
        copy(&temps, &temps, &temps_old);
        for (int x = 1; x<33; x++) {
            for (int y = 1; y<33; y++) {
               /* update array of temperatures */
               temps[x][y] = 0.25*(temps[x-1][y] +
                                   temps_old[x+1][y] +
                                   temps[x][y-1] +
                                   temps_old[x][y+1]);

               if (abs(temps_old[x][y]-temps[x][y]) > 0.0001) {
                   Continue = true;
               }
            }
        }
    }

    ofstream outfile;
    outfile.open("data/Q1_ii_temps_best.dat");
    for (int i=0; i<34; i++) {
        for (int j=0; j<34; j++) {
            outfile  << " " << temps[i][j];
        }
        outfile << "\n";
    }
    outfile.close();
    cout << "Fit converged after " << count << " Iterations.\n";
}
