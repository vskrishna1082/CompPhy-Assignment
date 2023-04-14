#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>

const int n=1200, dim = 3;

#include "moldyn.h"

int main()
{
    vector<int> neighbor_max_list;
    SimulationBox mybox;
    mybox.init_3dLattice();
    mybox.init_vel_with_temp(1);
    mybox.update_neighbor_list(); // create first neighbor list

    cout << mybox.calcPE() + mybox.getKE() << endl;
    /* run simulation for 50000 iterations allowing it to equilibriate */
    int equil_iter = 50000;
    for (int i = 0; i < equil_iter; i++) {
        mybox.verlet_step(true); // true -> uses neighbor_list
        if (i%100 == 0) {
            mybox.thermostat(1);
            cout << "=" << flush;
        }
        if (i%40 == 0) {
            mybox.update_neighbor_list();
            int max_neighbors = 0;
            for (int i = 0; i < n-1; i++) {
                int num_neighbors = mybox.neighbor_list[i].size();
                max_neighbors = (num_neighbors > max_neighbors) ?  num_neighbors : max_neighbors;
            }
            neighbor_max_list.push_back(max_neighbors);
        }
    }
    /* get range of neighbor_max_list */
    sort(neighbor_max_list.begin(), neighbor_max_list.end());
    cout << "\nRange of neighbors: [" << neighbor_max_list.front() << ", " << neighbor_max_list.back() << "].\n";


    /* run and collect data */
    cout << mybox.calcPE() + mybox.getKE() << endl;
    cout << mybox.getPE() + mybox.getKE() << endl;
    cout << endl;
}
