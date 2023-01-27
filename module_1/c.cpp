#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream myfile;
    myfile.open("test_ran.dat", ios::app); // open in append mode
    myfile << "\n# Changing seed and generating 10 new random numbers\n\n";
    myfile.close();
    return 0;
}
