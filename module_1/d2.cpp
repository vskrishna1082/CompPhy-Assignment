// 10 seeds, each producing 10 random numbers
// each seed's result in a different column
// 10 digits after the decimal

#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{

    /* Generate array of random doubles in (0,1) */
    double randomArray[10][10];
    uniform_real_distribution<double> u(0,1); // distribution common for all seeds

    for (int j=0; j<10; j++) // for every column
    {
        default_random_engine e;
        e.seed(j+1); // seed is set to column number+1
                     // seed 0 and 1 produce same numbers
        for (int i=0; i<10; i++) {
            randomArray[i][j] = u(e); 
    }}

    /* Print array into a file, columnwise */
    ofstream datafile;
    datafile.open("test_ran_10_seeds.dat");

    for (int j=0; j<10; j++)
    {
        for (int i=0; i<10; i++) {
            datafile << setprecision(10) << fixed << randomArray[j][i] << " ";
        } datafile << "\n";
    }
    datafile.close();
}
