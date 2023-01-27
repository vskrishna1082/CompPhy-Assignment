#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#define N_STEPS 1000
const double e = M_E;

double variance(int x)
{
    double variance = lgamma(N_STEPS - 1)-((lgamma((N_STEPS+x)*0.5 -1))+(lgamma((N_STEPS-x)*0.5 -1))+log(N_STEPS))+2*log(x);
    return variance;
}

int main() {
    double tot_variance=0;
    for (int i = 0; i<N_STEPS; i+=2) {
        tot_variance += variance(i);
    }
    cout << tot_variance << "\n";
    return 0;
}
