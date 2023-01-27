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
    const double coefficient = pow(sqrt(2*pi),-1);
    return coefficient*pow(e,exponent);
}

int main() {
    cout << trap_integrate(100000,-9,9,&func) << "\n";
}
