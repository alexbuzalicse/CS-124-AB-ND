#include <iostream>
#include <sstream>
#include <random>
#include<vector>


using std::vector;
using std::cout;
using std::endl;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::stoi;

double euclideanDistance(const vector<double> &x, const vector<double> &y) {
    double sum = 0;
    assert (x.size() == y.size());
    for (int i = 0; i < x.size(); i++) {
        sum += (x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(sum);
}

int main(int argc, char* argv[])
{
    // Get command line arguments
    int flexibleFlag = stoi(argv[1]);
    int n = stoi(argv[2]);
    int m = 65536;
    int trials = stoi(argv[3]);
    int dimension = stoi(argv[4]);

    // Declare variables
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0,1.0);
    vector<vector<double>> graph (n, vector<double>(dimension));

    // Random edge weight (dimension = 0)
    if (dimension == 0) {
        vector<vector<double>> adjacencyMatrix (n, vector<double>(n));
        for (int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                adjacencyMatrix[i][j] = distribution(generator);
                adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
            }
        }
    }
    else {
        // Generate graph, each row is a vertex with a point in (dimension) dimensions
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < dimension; j++) {
                graph[i][j] = distribution(generator);
            }
        }

        // Get adjacency matrix
        vector<vector<double>> adjacencyMatrix (n, vector<double>(n));
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                adjacencyMatrix[i][j] = euclideanDistance(graph[i], graph[j]);
            }
        }
    }
    
    return 0;
}