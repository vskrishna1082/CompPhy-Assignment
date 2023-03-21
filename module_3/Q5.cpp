#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int l_size = 10, J = 1, niter = 50000;
const double kbT = 3.9;
const int n_spins = l_size*l_size*l_size, L2 = l_size*l_size;

#include "ising.h"

int main()
{
    const double kbTinv = 1/kbT;
    vector<double> Evec_rand, Evec_1, Evec_m1, Mvec_rand, Mvec_1, Mvec_m1;

    IsingModel mylattice;
    mylattice.fillRandSpins();
    mylattice.kbT_inv = kbTinv;

    Evec_rand.push_back(mylattice.getTotalEnergy()/n_spins);
    Mvec_rand.push_back(mylattice.getMagMoment()/n_spins);
    for (int iter = 0; iter < niter; iter++)
    {
        mylattice.monteCarloSweep();
        Evec_rand.push_back(mylattice.getTotalEnergy()/n_spins);
        Mvec_rand.push_back(mylattice.getMagMoment()/n_spins);
    }

    mylattice.fillWith(1);
    Evec_1.push_back(mylattice.getTotalEnergy()/n_spins);
    Mvec_1.push_back(mylattice.getMagMoment()/n_spins);
    for (int iter = 0; iter < niter; iter++)
    {
        mylattice.monteCarloSweep();
        Evec_1.push_back(mylattice.getTotalEnergy()/n_spins);
        Mvec_1.push_back(mylattice.getMagMoment()/n_spins);
    }

    mylattice.fillWith(-1);
    Evec_m1.push_back(mylattice.getTotalEnergy()/n_spins);
    Mvec_m1.push_back(mylattice.getMagMoment()/n_spins);
    for (int iter = 0; iter < niter; iter++)
    {
        mylattice.monteCarloSweep();
        Evec_m1.push_back(mylattice.getTotalEnergy()/n_spins);
        Mvec_m1.push_back(mylattice.getMagMoment()/n_spins);
    }

    ofstream outfile_energy_rand;
    outfile_energy_rand.open("data/Q5_E_T-4.05_init_rand.dat");
    copy( Evec_rand.begin(), Evec_rand.end(), ostream_iterator<double>(outfile_energy_rand, "\n"));
    outfile_energy_rand.close();

    ofstream outfile_mag_rand;
    outfile_mag_rand.open("data/Q5_M_T-4.05_init_rand.dat");
    copy( Mvec_rand.begin(), Mvec_rand.end(), ostream_iterator<double>(outfile_mag_rand, "\n"));
    outfile_mag_rand.close();

    ofstream outfile_energy_1;
    outfile_energy_1.open("data/Q5_E_T-4.05_init_1.dat");
    copy( Evec_1.begin(), Evec_1.end(), ostream_iterator<double>(outfile_energy_1, "\n"));
    outfile_energy_1.close();

    ofstream outfile_mag_1;
    outfile_mag_1.open("data/Q5_M_T-4.05_init_1.dat");
    copy( Mvec_1.begin(), Mvec_1.end(), ostream_iterator<double>(outfile_mag_1, "\n"));
    outfile_mag_1.close();

    ofstream outfile_energy_m1;
    outfile_energy_m1.open("data/Q5_E_T-4.05_init_m1.dat");
    copy( Evec_m1.begin(), Evec_m1.end(), ostream_iterator<double>(outfile_energy_m1, "\n"));
    outfile_energy_m1.close();

    ofstream outfile_mag_m1;
    outfile_mag_m1.open("data/Q5_M_T-4.05_init_m1.dat");
    copy( Mvec_m1.begin(), Mvec_m1.end(), ostream_iterator<double>(outfile_mag_m1, "\n"));
    outfile_mag_m1.close();
}
