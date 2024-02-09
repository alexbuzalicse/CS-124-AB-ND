#include <iostream>
#include <sstream>
#include <random>

float euclideanDistance(std::vector<float> x, std::vector<float> y) {

    float sum = 0;

    for (int i = 0; i < x.size(); i++) {
        sum += (x[i]-y[i])*(x[i]-y[i]);
    }

    return sqrt(sum);
}

int main(int argc, char* argv[])
{

    // Get command line arguments
    int flexibleFlag = std::stoi(argv[1]);
    int n = std::stoi(argv[2]);
    int m = 65536;
    int trials = std::stoi(argv[3]);
    int dimension = std::stoi(argv[4]);

    // Declare variables
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    std::vector<std::vector<float>> graph (n, std::vector<float>(dimension));

    // Random edge weight (dimension = 0)
    if (dimension == 0) {
        
        std::vector<std::vector<float>> adjacencyMatrix (n, std::vector<float>(n));
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
        std::vector<std::vector<float>> adjacencyMatrix (n, std::vector<float>(n));
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                adjacencyMatrix[i][j] = euclideanDistance(graph[i], graph[j]);
            }
        }
    }
    
    return 0;
}