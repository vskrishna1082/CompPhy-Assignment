/* trapezoidal integration of sin(x) */
#include <iostream>
#include <iomanip>
#include <cmath>
#include "trap_integrator.h"
using namespace std;

const double pi=M_PI;

int main() {
    cout << trap_integrate(10000,0,pi,&sin) << "\n";
}
