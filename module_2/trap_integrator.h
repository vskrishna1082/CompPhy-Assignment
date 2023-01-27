/* Estimates definite integral of a function using 
 * trapezoidal integration */

/* Usage: trap_integrate(number_of_bins, lr_bound, ur_bound, &function)*/
double trap_integrate(int n_bins,double l_bound,double u_bound, double (*func)(double))
{
    const double dx = (u_bound - l_bound)/n_bins;
    double trap_area=0;
    trap_area += 0.5*(func(l_bound) + func(u_bound));
#pragma omp parallel for shared(dx),reduction(+:trap_area)
    for (long i=1; i<n_bins; i++) {
        trap_area += func(l_bound + i*dx);
    }
    trap_area *= dx;
    return trap_area;
}
