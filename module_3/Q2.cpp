#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int l_size = 10, J = 1; // const for using arrays 
const int n_spins = l_size*l_size*l_size, L2 = l_size*l_size;

#include "ising.h"

int main()
{
    IsingModel mylattice;
    mylattice.fillWith(1);
    cout << mylattice.getTotalEnergy() << endl;
}
