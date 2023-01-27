/* Generate random numbers between 0 and 1 */
#include <iostream>
#include <random>
#include <fstream>
/* #include <ctime> */
#include <cmath>
#include <vector>
#include <iterator>
using namespace std;

int main() {
    int n=0;
    cout << "Enter number of random numbers: ";
    cin >> n;

    mt19937 e; // use Marsenne-Twister random number generator
    e.seed(time(0));
    uniform_real_distribution<double> u(0,1);

    vector<double> rand_array;
    double mean=0;
    double var=0;

    ofstream datafile;
    datafile.open("uniform_rand_0_1.dat");
    for (int i=0; i<n; ++i)
    {
        double random_number=u(e);
        rand_array.push_back(random_number);
        mean += random_number;
    }
    mean = mean/(double) n;
    /* copy(rand_array.begin(), rand_array.end(), ostream_iterator<double>(cout, "\n")); */
    datafile.close();

    for (auto& n : rand_array) {
        var += n*n - mean*mean;
    }
    var = var/(double) n;
    double error = abs(mean - 0.5000000);
    cout << error << " " << var << "\n";
    return 0;
}
