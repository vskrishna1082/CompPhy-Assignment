#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int l_size = 10, J = 1, niter = 50000;
const double kbT = 4.9;
const int n_spins = l_size*l_size*l_size, L2 = l_size*l_size;

#include "ising.h"

int main()
{
    const double kbTinv = 1/kbT;
    vector<double> Mvec;

    IsingModel mylattice;
    mylattice.fillWith(1);
    mylattice.kbT_inv = kbTinv;

    Mvec.push_back(mylattice.getMagMoment()/n_spins);
    for (int iter = 0; iter < niter; iter++)
    {
        mylattice.monteCarloSweep();
        Mvec.push_back(mylattice.getMagMoment()/n_spins);
    }

    ofstream outfile;
    outfile.open("data/Q3_M_T-4.9_init_1.dat");
    copy( Mvec.begin(), Mvec.end(), ostream_iterator<double>(outfile, "\n"));
    outfile.close();
}
