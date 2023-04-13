#include <iostream>
#include <iomanip>

const int n=729, dim = 3;

#include "moldyn.h"

int main()
{
    SimulationBox mybox;
    mybox.init_3dLattice();
    mybox.init_vel();
    cout << mybox.getKE() << endl;
    cout << mybox.getTemp() << endl;
    cout << mybox.get_total_MV()[0] << endl;
    cout << mybox.get_total_MV()[1] << endl;
    cout << mybox.get_total_MV()[2] << endl;
}
