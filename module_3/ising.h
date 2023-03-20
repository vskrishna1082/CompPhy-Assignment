#include <random>
#include <array>
#include <cmath>
using namespace std;

template <typename T, size_t I>
using array3d = array<array<array<T,I>,I>,I>;

extern const int l_size, n_spins, L2;

class IsingModel {
    public:
        array3d<int, l_size> spins;
        size_t size = l_size;
        double kbT_inv = 1.0;
        int n = n_spins;

        struct index {int i; int j; int k;}; /* define an index */

        /* fill lattice with random seq of spins */
        void fillRandSpins(int seed = 0)
        {
            int spinarray[2] = {-1,1};
            mt19937 e(seed); // Marsenne-Twister random engine
            uniform_int_distribution<> u(0,1);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        spins[i][j][k] = spinarray[u(e)];
                    }
                }
            }
        }

        /* get total magnetic moment of lattice */
        double getMagMoment()
        {
            double mag_moment = 0;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        mag_moment += spins[i][j][k];
                    }
                }
            }
            return mag_moment;
        }

        /* get energy of dipole at index (i,j,k) */
        double getLocalEnergy(struct index idx)
        {
            /* apply boundary conditions */
            int idxx_prev = (idx.i != 0) ? idx.i-1 : size - 1;
            int idxx_next = (idx.i != size - 1) ? idx.i+1 : 0;

            int idxy_prev = (idx.j != 0) ? idx.j-1 : size - 1;
            int idxy_next = (idx.j != size - 1) ? idx.j+1 : 0;

            int idxz_prev = (idx.k != 0) ? idx.k-1 : size - 1;
            int idxz_next = (idx.k != size - 1) ? idx.k+1 : 0;

            int localSpin = spins[idx.i][idx.j][idx.k];
            return -J*localSpin*(spins[idxx_prev][idx.j][idx.k] +
                                 spins[idxx_next][idx.j][idx.k] +
                                 spins[idx.i][idxy_prev][idx.k] +
                                 spins[idx.i][idxy_next][idx.k] +
                                 spins[idx.i][idx.j][idxz_prev] +
                                 spins[idx.i][idx.j][idxz_next]);
        }

        double getTotalEnergy()
        {
            double totalEnergy = 0;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        struct index idx = {i,j,k};
                        totalEnergy += getLocalEnergy(idx);
                    }
                }
            }
            return totalEnergy / 2;
        }

        /* attempt L*L*L random spin flips + Metropolis criterion */
        void monteCarloSweep()
        {
            mt19937 e;
            uniform_int_distribution<> u_int(0,L2 - 1);
            uniform_real_distribution<double> u_mp(0,1);
            for (int i = 0; i < n; i++)
            {
                /* generate a random number and convert it into an index */
                struct index idx = i_to_idx(u_int(e));
                double dE = -2*getLocalEnergy(idx);
                if (dE < 0) {
                    flip_spin(idx);
                }
                else {
                    double u = exp(-dE*kbT_inv);
                    double r = u_mp(e);
                    if (r < u) {
                        flip_spin(idx);
                    }
                }
            }
        }

    private:
        struct index i_to_idx(int i) {
            return {i/L2, (i/size)%size, i%size};
        }

        void flip_spin(struct index idx) {
            spins[idx.i][idx.j][idx.k] *= -1;
        }
};
