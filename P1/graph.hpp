#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <set>

using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::stoi;

default_random_engine generator;
uniform_real_distribution<double> uniformDistribution(0.0,1.0);

class Graph {
    private:
    int n;
    vector<vector<int>> adj_list;
    set<int> seen_vertices;
    vector<int> distances;

    public:
    
    Graph() {}
    
    Graph (int n) : n(n) {
        vector<vector<int>> temp(n);
        adj_list = temp;
        vector<int> temp2(n);
        distances = temp2;
    }
    ~Graph () {}

    vector<vector<int>> get_adj_list() const {
        return adj_list;
    }

    vector<int> get_distances() const {
        return distances;
    }

    void dist_tester() {
        distances[1] = 1;
    }

    int get_size() const {
        return n;
    }
};


double euclideanDistance(const vector<double> &x, const vector<double> &y) {
    double sum = 0;
    assert (x.size() == y.size());
    for (int i = 0; i < x.size(); i++) {
        sum += (x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(sum);
}

vector<vector<double>> getAdjacencyMatrix(int dimension, int n) {

    vector<vector<double>> adjacencyMatrix (n, vector<double>(n));

    // Random edge weight (dimension = 0)
    if (dimension == 0) {

        for (int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                adjacencyMatrix[i][j] = uniformDistribution(generator);
                adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
            }
        }
    }

    else {

        vector<vector<double>> graph (n, vector<double>(dimension));

        // Generate graph, each row is a vertex with a point in (dimension) dimensions
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < dimension; j++) {
                graph[i][j] = uniformDistribution(generator);
            }
        }

        // Get adjacency matrix
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                adjacencyMatrix[i][j] = euclideanDistance(graph[i], graph[j]);
            }
        }
    }

    return adjacencyMatrix;
}

void printMatrix(vector<vector<double>> matrix) {

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0 ; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}