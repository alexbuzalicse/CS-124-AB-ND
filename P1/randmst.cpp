#include <iostream>
#include <sstream>
#include <random>

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

    // float graph[n][n][dimension];
    std::vector<std::vector<std::vector<float> > > graph (n, std::vector<std::vector<float> >(n, std::vector<float>(dimension)));

    // Generate graph
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for (int k = 0; k < dimension; k++) {
                graph[i][j][k] = distribution(generator);
            }
        }
    }

    // Print graph
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         std::cout << "(";
    //         for (int k = 0; k < dimension; k++) {
    //             std::cout << graph[i][j][k];
    //             if (k != dimension -1) {
    //                 std::cout << ", ";
    //             }
    //         }
    //         std::cout << ") ";
    //     }
    //     std::cout << std::endl;
    // }  

    return 0;
}