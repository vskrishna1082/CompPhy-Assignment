#include <iostream>
#include <random>
using namespace std;


// rand() and srand() are (apparently) obsolete c++ functions
// included here for completeness
void gen_badRand()
{
    double randomNumber[10]; // rand*8 = double
    srand(1); // default seed
    for(int i=0;i<10;i++)
    {
        randomNumber[i] = rand()/ (double) RAND_MAX; // restrict to [0,1]
        cout << randomNumber[i] << endl; 
    }
}

// better random number generator - c++11 and above
void gen_Rand()
{
    default_random_engine e; 
    uniform_real_distribution<double> u(0,1);
    for (int i = 0; i < 10; i++) {
        cout << u(e) << "\n";
    }
}

int main() 
{
    cout << "Old Random Numbers:\n";
    gen_badRand();
    cout << "\nBetter Random Numbers:\n";
    gen_Rand();
}
