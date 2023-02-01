/* Estimates definite integral of a function using 
 * trapezoidal integration */

/* Usage: trap_integrate(number_of_bins, lr_bound, ur_bound, &function)*/
double trap_integrate(int n_bins,double l_bound,double u_bound, double (*func)(double))
{
    double dx = (u_bound - l_bound)/(double) n_bins;
    double trap_area=0;
    trap_area += 0.5*(func(u_bound) - func(l_bound));
#pragma omp parallel for shared(dx),reduction(+:trap_area)
    for (int i=0; i<n_bins; i++) {
        trap_area += func(l_bound + i*dx);
    }
    trap_area *= dx;
    return trap_area;
}
