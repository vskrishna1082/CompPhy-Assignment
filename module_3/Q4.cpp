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
    vector<double> Evec;

    IsingModel mylattice;
    mylattice.fillRandSpins();
    mylattice.kbT_inv = kbTinv;

    Evec.push_back(mylattice.getTotalEnergy()/n_spins);
    for (int iter = 0; iter < niter; iter++)
    {
        mylattice.monteCarloSweep();
        Evec.push_back(mylattice.getTotalEnergy()/n_spins);
    }

    ofstream outfile;
    outfile.open("data/Q4_E_T-3.9_init_rand.dat");
    copy( Evec.begin(), Evec.end(), ostream_iterator<double>(outfile, "\n"));
    outfile.close();
}
