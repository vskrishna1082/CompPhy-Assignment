/* Integrating a normalized gaussian between symmetric intervals*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include "trap_integrator.h"
using namespace std;

const double pi=M_PI;
const double e=M_E;

double func(double x) {
    double exponent = -(pow(x,2)*0.5);
    double coefficient = pow(sqrt(2*pi),-1);
    return coefficient*exp(exponent);
}

int main() {
    cout << setprecision(15) << trap_integrate(10000,-3,3,&func) << "\n";
}
