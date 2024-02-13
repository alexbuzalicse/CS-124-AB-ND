#include "graph.cpp"
#include "heap.cpp"

int main(int argc, char* argv[])
{
    // Get command line arguments
    int flexibleFlag = stoi(argv[1]);
    int n = stoi(argv[2]);
    int m = 65536;
    int trials = stoi(argv[3]);
    int dimension = stoi(argv[4]);

    // Generate adjacency matrix
    vector<vector<double>> adjacencyMatrix = getAdjacencyMatrix(dimension, n);

    return 0;
}