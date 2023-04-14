#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>

const int n=2197, dim = 3;

#include "moldyn.h"

int main()
{
    vector<double> KE_list;
    vector<double> PE_list;
    SimulationBox mybox;
    mybox.init_3dLattice();
    mybox.init_vel_with_temp(1);
    int iter = 20000;
    for (int i = 0; i < iter; i++) {
        mybox.verlet_step();
        KE_list.push_back(mybox.getKE());
        PE_list.push_back(mybox.getPE());
        if (i%100 == 0) {
            mybox.thermostat(1);
            cout << "=" << flush;
        }
    }
    cout << endl;

    ofstream kefile, pefile;
    kefile.open("data/Q3_KE.dat");
    copy(KE_list.begin(), KE_list.end(), ostream_iterator<double>(kefile, "\n"));
    pefile.open("data/Q3_PE.dat");
    copy(PE_list.begin(), PE_list.end(), ostream_iterator<double>(pefile, "\n"));
    kefile.close();
    pefile.close();
}
