#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int l_size = 9, J = 1, niter = 1010000;
const int n_spins = l_size*l_size*l_size, L2 = l_size*l_size;
const double kbT_i = 3.8, kbT_f = 4.7, dT = 0.02;
/* calculate steps between initial and final temperatures */
const int n_T = (int) ( (kbT_f - kbT_i) / dT) + 1;

#include "ising.h"

int main()
{
    double kbT = kbT_i; /* initialize kbT */

    /* generate an array of vectors for every temperature
     * Evec[i] is the evolution of lattice for T = kbT_i + i*dt*/
    array<vector<double>, n_T> Evec, Mvec;

    IsingModel mylattice; /* init the lattice */

    for (int i = 0; i < n_T; i++) /* loop over all temps */
    {
        mylattice.fillRandSpins(); /* refill lattice */
        mylattice.kbT_inv = 1/kbT; /* set temp of lattice */

        Evec[i].push_back(mylattice.getTotalEnergy()/n_spins);
        Mvec[i].push_back(mylattice.getMagMoment()/n_spins);
        for (int iter = 0; iter < niter; iter++)
        {
            mylattice.monteCarloSweep();
            Evec[i].push_back(mylattice.getTotalEnergy()/n_spins);
            Mvec[i].push_back(mylattice.getMagMoment()/n_spins);
        }
        cout << kbT << " " << flush;
        kbT += dT; // increment kbT
    }

    cout << "\n";

    /* write everything to files */
    ofstream energyfile, magfile, magmodfile;
    energyfile.open("data/Q7-8-9-Energy_Avg_l_9.dat");
    magfile.open("data/Q7-8-9-Mag_Avg_l_9.dat");
    magmodfile.open("data/Q7-8-9-Mag_Mod_Avg_l_9.dat");
    for (int i = 0; i < n_T; i++)
    {
        const int cutoff = 10000;
        const long n_good = niter - cutoff;
        double E_av = 0, E2_av = 0, M_av = 0, M2_av=0, absM_av=0, M4_av=0;
        for (int j = cutoff; j < Evec[0].size(); j++ ) {
            E_av += Evec[i][j];
            E2_av += Evec[i][j]*Evec[i][j];
        }
        for (int j = cutoff; j < Mvec[0].size(); j++ ) {
            M_av += Mvec[i][j];
            M2_av += Mvec[i][j]*Mvec[i][j];
            absM_av += abs(Mvec[i][j]);
            M4_av += Mvec[i][j]*Mvec[i][j]*Mvec[i][j]*Mvec[i][j];
        }
        E_av = E_av / n_good;
        M_av = M_av / n_good;
        absM_av = absM_av / n_good;
        E2_av = E2_av / n_good;
        M2_av = M2_av / n_good;
        M4_av = M4_av / n_good;

        energyfile << E_av << " " << E2_av << "\n";
        magfile << M_av << " " << M2_av << " " << M4_av << "\n";
        magmodfile << absM_av << " " << M2_av << "\n";
    }
    energyfile.close();
    magfile.close();
    magmodfile.close();
}
