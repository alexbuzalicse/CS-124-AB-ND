#include "algos.hpp"

int main(int argc, char* argv[])
{
    int flexibleFlag;
    int n;
    int dimension;
    int trials;

    if (argc > 1)  {
        // Get command line arguments
        flexibleFlag = stoi(argv[1]);
        n = stoi(argv[2]);
        trials = stoi(argv[3]);
        dimension = stoi(argv[4]);
    }  

    double sum = 0;
    cout << "Individual Trials: ";
    for (int i = 0; i < trials; i++) {
        double mstSum = prim_MST(n, dimension);
        sum += mstSum;
        cout << mstSum << " ";
    }
    cout << "\nAverage: " << sum/trials;

    return 0;
}

