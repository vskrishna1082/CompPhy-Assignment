/* Header file for SimulationBox class. Requires const particle count 
 *  and dimension to be initialized before inclusion */

#include <random>
#include <algorithm>
#include <iostream>
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
    double PE = 0; // PE is calculated alongside lj_force to save on comp. cost
    public:
        double l_x = 20, l_y = 20, l_z = 20; // dim. of box
        double sigma = 1, epsilon = 4; // parameters of potential
        double r_c = 2.5, neighbor_dist = 4.5; // cutoff parameters
        double m = 1;
        double dt = 0.005;
        attr_array<double, n, dim> pos, vel, force;
        attr_array<double, n, dim> &acc = force;
        array<vector<int>, n> neighbor_list;

        /*****************************/
        /* Simulation Initialization */
        /*****************************/

        void init_3dLattice() // assumes that box is cubic
        {
            bool iscube = false;
            int n_l = cbrt(n); // particles per axis
            int n_l_sq = n_l*n_l;
            double dl = l_x / n_l; // dist between lattice pts
            double offset = dl/2; // offset to handle overlap at boundary
            if (floor(cbrt(n)) == cbrt(n)) {
                iscube = true;
            }
            switch(iscube) {
                case true: // if n is a perfect cube arrange in lattice
                    for (int i = 0; i < n; i++) {
                        pos[i][0] = (i/n_l_sq)*dl + offset; // with idx1, set pos
                        pos[i][1] = ((i/n_l)%n_l)*dl + offset; // second index
                        pos[i][2] = (i%n_l)*dl + offset; // third index
                    }
                    /* apply PBC to pos */
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < dim; j++) {
                            pos[i][j] = pos[i][j] - l_x*round(pos[i][j]/l_x);
                        }
                    }
                    break;

                case false: // create a bigger lattice and fill n points in it
                    n_l += 1; // increment n_l
                    n_l_sq = n_l*n_l;
                    dl = l_x / n_l;
                    offset = dl/2;

                    vector<int> int_list(n_l*n_l*n_l); // vector of size n
                    iota(begin(int_list), end(int_list), 0); // fill with 0,...,n-1
                    auto rng = default_random_engine {};
                    shuffle(begin(int_list), end(int_list), rng); // shuffle it

                    for (int i = 0; i < n; i++) {
                        int idx = int_list[i];
                        pos[i][0] = (idx/n_l_sq)*dl + offset; // with idx1, set pos
                        pos[i][1] = ((idx/n_l)%n_l)*dl + offset; // second index
                        pos[i][2] = (idx%n_l)*dl + offset; // third index
                    }
                    break;
            }
        }

        void init_vel_with_temp(double kbT = 1)
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

        /************/
        /* Dynamics */
        /************/

        void verlet_step(bool use_neighbor_list = false)
        {
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < dim; j++) {
                    vel[i][j] = vel[i][j] + 0.5*dt*acc[i][j]; // int. velocity in verlet step
                    pos[i][j] = pos[i][j] + dt*vel[i][j]
                        - l_x*round((pos[i][j] + dt*vel[i][j])/l_x); //PBC: round(pos+dt*v) = 0 inside

                }
            }
            /* recompute acc */
            force = {0};
            switch (use_neighbor_list) {
                case false:
                    force_update_full();
                    break;
                case true:
                    force_update_neighbors();
                    break;
            }
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < dim; j++) {
                    vel[i][j] = vel[i][j] + 0.5*dt*acc[i][j]; // int. velocity in verlet step
                }
            }
        }

        /***************************/
        /* Simulation Fine-tuneing */
        /***************************/

        void thermostat(double kbT = 1)
        {
            double scale = sqrt(kbT/getTemp());
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < dim; j++) {
                    vel[i][j] *= scale;
                }
            }
        }

        void update_neighbor_list()
        {
#pragma omp parallel for
            for (int i = 0; i < n-1; i++) {
                neighbor_list[i].clear();
                for (int j = i+1; j < n; j++) {
                    double r_diff[dim];
                    double rij_sq=0;
                    for (int k = 0; k<dim; k++)
                    {
                        r_diff[k] = pos[i][k] - pos[j][k]
                             -l_x*round((pos[i][k] - pos[j][k])/l_x);
                        rij_sq += r_diff[k]*r_diff[k];
                    }
                    /* add particle to list if it is within neighbor cutoff */
                    if (rij_sq < neighbor_dist_sq) {
                        neighbor_list[i].push_back(j);
                    }
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

        /* get temperature of box */
        double getTemp()
        {
            return getKE()/(1.5*n); /* KE = (3/2)*n*kbT */
        }

        /* simply returns potential energy of box 
         * relies on lj_force computation keeping 
         * PE up to date */
        double getPE()
        {
            return PE;
        }

        /* computationally intensive PE calculation, use sparsely! */
        double calcPE()
        {
            double pe = 0;
#pragma omp parallel for reduction(+:pe)
            for (int i = 0; i < n-1; i++) {
                for (int j = i+1; j < n; j++) {
                    double rij_sq = 0, r_diff[dim];
                    double sr2, sr6, sr12;
                    for (int k = 0; k<dim; k++)
                    {
                        r_diff[k] = pos[i][k] - pos[j][k];
                        r_diff[k] = r_diff[k] - l_x*round(r_diff[k]/l_x);
                        rij_sq += r_diff[k]*r_diff[k];
                    }
                    /* move to next particle if dist > cutoff */
                    if (rij_sq < r_c_sq) {
                        double pe_ij = lj_mod_pot(rij_sq);
                        pe += pe_ij;
                    }
                }
            }
            return pe;
        }

        /* return an array with total momenta along each axis */
        array<double, dim> getMV()
        {
            array<double, dim> mv = {0};
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < dim; j++) {
                    mv[j] += vel[i][j];
                }
            }
            return mv;
        }

        SimulationBox() {gen_constants();}
    /* private: */
        double sigma_sq, r_c_sq, neighbor_dist_sq, f0, u0;
        
        /* returns (actual) lj_potential between particles at distance r */
        double lj_pot(double r_sq)
        {
            double sr2 = sigma_sq/r_sq;
            double sr6 = sr2*sr2*sr2;
            double sr12 = sr6*sr6;
            return epsilon*(sr12 - sr6);
        }
        /* actual force (divided by mag_r) for particles sep by r */
        double lj_force(double r_sq)
        {
            double sr2 = sigma_sq/r_sq;
            double sr6 = sr2*sr2*sr2;
            double sr12 = sr6*sr6;
            return epsilon*(12*sr12 - 6*sr6)/r_sq;
        }

        void gen_constants()
        {
            sigma_sq = sigma*sigma;
            r_c_sq = r_c*r_c;
            neighbor_dist_sq = neighbor_dist*neighbor_dist;
            f0 = lj_force(r_c_sq);
            u0 = 0.5*f0*r_c_sq + lj_pot(r_c_sq);
            cout << "Initialized constants" << endl;
        }

        /* modified lj potential */
        double lj_mod_pot(double r_sq) {
            return lj_pot(r_sq) + 0.5*f0*r_sq - u0;
        }

        /* modified lj force */
        double lj_mod_force(double r_sq) {
            return lj_force(r_sq) - f0;
        }

        struct f_and_pot {
            double force;
            double potential;
        };

        /* computes both force and potential */
        struct f_and_pot lj_mod_f_and_pot(double r_sq)
        {
            double sr2 = sigma_sq/r_sq;
            double sr6 = sr2*sr2*sr2;
            double sr12 = sr6*sr6;
            double force = epsilon*(12*sr12 - 6*sr6)/r_sq - f0;
            double pot = epsilon*(sr12 - sr6) + 0.5*f0*r_sq - u0;
            return {force, pot};
        };

        /* compute force, comparing all particle pairs */
        void force_update_full()
        {
            PE = 0;
#pragma omp parallel for reduction(+:PE)
            for (int i=0; i<n-1; i++) {
                for (int j = i+1; j < n; j++) {
                    double rij_sq = 0, r_diff[dim];
                    double sr2, sr6, sr12;
                    for (int k = 0; k<dim; k++)
                    {
                        r_diff[k] = pos[i][k] - pos[j][k];
                        r_diff[k] = r_diff[k] - l_x*round(r_diff[k]/l_x);
                        rij_sq += r_diff[k]*r_diff[k];
                    }
                    /* move to next particle if dist > cutoff */
                    if (rij_sq < r_c_sq) {
                        struct f_and_pot fp = lj_mod_f_and_pot(rij_sq);
                        PE += fp.potential;
#pragma omp critical
                        for (int k = 0; k < dim; k++) {
                            force[i][k] += fp.force*r_diff[k];
                            force[j][k] -= fp.force*r_diff[k];
                        }
                    }
                }
            }
        }

        void force_update_neighbors()
        {
            PE = 0;
#pragma omp parallel for reduction(+:PE)
            for (int i=0; i<n-1; i++) {
                for (int n = 0; n < neighbor_list[i].size(); n++) {
                    int j = neighbor_list[i][n];
                    double rij_sq = 0, r_diff[dim];
                    double sr2, sr6, sr12;
                    for (int k = 0; k<dim; k++)
                    {
                        r_diff[k] = pos[i][k] - pos[j][k];
                        r_diff[k] = r_diff[k] - l_x*round(r_diff[k]/l_x);
                        rij_sq += r_diff[k]*r_diff[k];
                    }
                    /* move to next particle if dist > cutoff */
                    if (rij_sq < r_c_sq) {
                        struct f_and_pot fp = lj_mod_f_and_pot(rij_sq);
                        PE += fp.potential;
#pragma omp critical
                        for (int k = 0; k < dim; k++) {
                            force[i][k] += fp.force*r_diff[k];
                            force[j][k] -= fp.force*r_diff[k];
                        }
                    }
                }
            }
        }
};
