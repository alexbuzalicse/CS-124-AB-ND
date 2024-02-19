#include "algos.hpp"

int main(int argc, char* argv[])
{
    int flexibleFlag = 0; // changing to zero to avoid non-init issues
    int n = 0;
    int dimension = 0;
    int trials = 0;

    if (argc > 1)  {
        // Get command line arguments
        flexibleFlag = stoi(argv[1]);
        n = stoi(argv[2]);
        trials = stoi(argv[3]);
        dimension = stoi(argv[4]);
    }  

    double mstAverage = 0;
    double maxEdgeAverage = 0;
    cout << "Individual Trials\n";
    for (int i = 0; i < trials; i++) {
        auto [mstSum, maxEdge] = prim_MST(n, dimension);
        mstAverage += mstSum;
        maxEdgeAverage += maxEdge;
        cout << "Tree Weight: " << mstSum << ", " << "Max Edge: " << maxEdge << "\n";
    }
    cout << "\nAverage MST Weight: " << mstAverage/trials << "\n";
    cout << "\nAverage Max Edge: " << maxEdgeAverage/trials << "\n";

    return 0;
}

