#include <iostream>
#include <iomanip>
#include <fstream>
#include <complex>
#include <vector>
#include <array>
#include <cmath>
#include <Eigen/Eigenvalues>
using namespace std;

const double pi = M_PI;

/* number of basis elements - more is better */
const int n = 50, npw = 2*n +1;
double v0=1, a=5, b=2;
double kn[npw];
Eigen::Matrix<double, npw, npw> H; // create npw x npw matrix

void fill_kvector()
{
    kn[0] = 0;
    for (int i = 1; i < npw-1; i+=2) {
        kn[i] = (((i+1)/2.0)*2.0*pi/a);
        kn[i+1] = -(((i+1)/2.0)*2.0*pi/a);
    }
}

void fill_hmatrix()
{
    for (int idx = 0; idx < npw*npw; idx++) {
        int j = idx/npw; // column major index extraction
        int i = idx%npw;
        H(i,j) = (i != j) ? -v0/a * sin((kn[j] - kn[i])*b/2.0) / (kn[j] - kn[i])*2.0 // derived for diff i and j
                : kn[i]*kn[i] - v0/a*b;
    }
}


int main()
{
    while (a < 30) {
        fill_kvector();
        fill_hmatrix();
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(H);
        Eigen::MatrixXd E = es.eigenvalues();
        cout << setw(2) << (int) a <<  " " << setprecision(6) << fixed << E(0) << endl;
        a += 2;
    }
        return 0;
}
