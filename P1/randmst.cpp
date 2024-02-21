#include "algos.hpp"

int main(int argc, char* argv[])
{
    int flexibleFlag = 0;
    int n = 0;
    int dimension = 0;
    int trials = 0;

    if (argc > 1)  {
        flexibleFlag = stoi(argv[1]);
        n = stoi(argv[2]);
        trials = stoi(argv[3]);
        dimension = stoi(argv[4]);
    }  

    double mstAverage = 0;
    double maxEdgeAverage = 0;
    for (int i = 0; i < trials; i++) {
        auto [mstSum, maxEdge] = prim_MST(n, dimension);
        mstAverage += mstSum;
        maxEdgeAverage += maxEdge;
    }
    
    cout << mstAverage/trials << " " << n << " " << trials << " " << dimension;

    return 0;
}

