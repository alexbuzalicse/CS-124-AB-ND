#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <set>
#include <unordered_map>

using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::uniform_real_distribution;
using std::stoi;
using std::unordered_map;

std::random_device rd;
std::mt19937 generator(rd());
uniform_real_distribution<double> uniformDistribution(0.0,1.0);

double euclideanDistance(const vector<double> &x, const vector<double> &y) {
    double sum = 0;
    assert (x.size() == y.size());
    for (int i = 0; i < x.size(); i++) {
        sum += (x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(sum);
}

class Graph {
    private:
    int n;
    unordered_map<int, unordered_map<int, double>> adj_list;
    set<int> seen_vertices;
    vector<double> distances;
    vector<int*> prev_verts;

    public:
    
    Graph() {}
    
    Graph (int n) : n(n) {
        vector<double> temp2(n, __DBL_MAX__);
        distances = temp2;
        distances[0] = 0.0;
        vector<int*> temp3(n);
        for (int* &ptr : temp3) ptr = nullptr; // all prev start as nullptr
        prev_verts = temp3;
    }
    ~Graph () {}

    unordered_map<int, unordered_map<int, double>> get_adj_list() const {
        return adj_list;
    }

    vector<double> get_distances() const {
        return distances;
    }

    double get_distance(int v) const {
        return distances[v];
    }

    void set_distance(int vert, double dist) {
        distances[vert] = dist;
    }

    bool seen_vertex(int v) const {
        return seen_vertices.find(v) != seen_vertices.end();
    }

    int get_size() const {
        return n;
    }

    unordered_map<int, double>& get_vertex(int v) { return adj_list[v]; }

    int* get_prev_index(int v) const { return prev_verts[v]; }

    double edge_weight(int i, int j) {

        if (i == j) return 0;

        if (i < j) {
            if (!adj_list[i].size()) return 0;
            if (adj_list[i].find(j) == adj_list[i].end()) return 0;
            return adj_list[i][j];
        }
        
        return edge_weight(j,i);
        
    }

    void add_seen_vertex(int v) {
        seen_vertices.insert(v);
    }

    void initialize_adjacency_list (int dimension) {

        // Random edge weight (dimension = 0)
        if (dimension == 0) {
            for (int i = 0; i < n; i++) {
                for(int j = i+1; j < n; j++) {
                    adj_list[i][j] = uniformDistribution(generator);
                }
            }
        }

        else {

            // Generate vertices, each row is a vertex with a point in (dimension) dimensions
            vector<vector<double>> vertices (n, vector<double>(dimension));
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < dimension; j++) {
                    vertices[i][j] = uniformDistribution(generator);
                }
            }
            
            // Generate adjacency list
            for (int i = 0; i < n; i++) {
                for (int j = i+1; j < n; j++) {
                    adj_list[i][j] = euclideanDistance(vertices[i], vertices[j]);
                }
            }
        }

    }
};

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

