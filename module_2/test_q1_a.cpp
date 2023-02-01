#include <iostream>
#include <iomanip>
#include <cmath>
#include "trap_integrator.h"
using namespace std;

const double pi=M_PI;

double sqfunc(double x) {
    return 4/(1+x*x);
}

int main()
{
    int it = 100000;
    cout << setw(3) << left << log10(it) << ":" << log10(abs(pi - trap_integrate(it, 0, 1, &sqfunc))) << "\n";
}
