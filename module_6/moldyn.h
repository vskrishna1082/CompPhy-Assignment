/* Header file for SimulationBox class. Requires const particle count 
 *  and dimension to be initialized before inclusion */

#include <random>
#include <array>
#include <vector>
#include <cmath>
using namespace std;

/* template for particle attributes */
template <typename T, size_t N, size_t DIM>
using attr_array = array<array<T, DIM>, N>;

extern const int n, dim;

class SimulationBox
{
    double l_x = 30, l_y = 30, l_z = 30; // dim. of box, init with Box declaration
    double sigma = 1, epsilon = 1; // parameters of potential
    double r_c = 2, neighbor_dist = 10; // cutoff parameters
    double m = 1;
    public:
        attr_array<double, n, dim> pos, vel, acc;
        array<vector<int>, n> neighbor_list;

        /*****************************/
        /* Simulation Initialization */
        /*****************************/

        void init_3dLattice() // assumes that n and box are perfect cubes
        {
            int n_l = cbrt(n); // particles per axis
            int n_l_sq = n_l*n_l;
            double dl = l_x / n_l; // dist between lattice pts
            double offset = 0;//dl/2; // offset to handle overlap at boundary
            for (int i = 0; i < n; i++) {
                pos[i][0] = (i/n_l_sq)*dl + offset; // get first index and set pos
                pos[i][1] = ((i/n_l)%n_l)*dl + offset; // second index
                pos[i][2] = (i%n_l)*dl + offset; // third index
            }
            /* apply PBC to pos */
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < dim; j++) {
                    pos[i][j] = pos[i][j] - l_x*round(pos[i][j]/l_x);
                }
            }
        }

        void init_vel(double kbT = 1)
        {
            double A = sqrt(12*kbT/m);
            default_random_engine e;
            uniform_real_distribution<double> u(-0.5*A, 0.5*A);

            /* assign velocities randomly */
            double vel_av[3] = {0,0,0}; /* average velocity */
            for (int i = 0; i < n; i++){
                for (int j = 0; j < dim; j++) {
                    vel[i][j] = u(e);
                    vel_av[j] += vel[i][j]/n;
                }
            }

            /* set momentum to 0*/
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < dim; j++) {
                    vel[i][j] -= vel_av[j];
                }
            }
        }

        /*************************/
        /* Simulation Statistics */
        /*************************/

        /* get kinetic energy */
        double getKE()
        {
            double ke = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < dim; j++) {
                    ke += vel[i][j]*vel[i][j];
                }
            }
            return 0.5*ke;
        }

        /* get temperatur of box */
        double getTemp()
        {
            return getKE()/(1.5*n); /* KE = (3/2)*n*kbT */
        }

        /* return an array with total momenta along each axis */
        array<double, dim> get_total_MV()
        {
            array<double, dim> mv = {0};
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < dim; j++) {
                    mv[j] += vel[i][j];
                }
            }
            return mv;
        }
};
