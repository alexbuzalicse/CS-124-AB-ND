#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <set>
#include <unordered_map>
#include "KDTree.hpp"

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
    // assert (x.size() == y.size());
    for (int i = 0; i < x.size(); i++) {
        sum += (x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(sum);
}

double gen_dist(int dimension) {
    vector<double> v1(dimension), v2(dimension);
    for (int i = 0; i < dimension; ++i) {
        v1[i] = uniformDistribution(generator);
        v2[i] = uniformDistribution(generator);
    }
    return euclideanDistance(v1, v2);
}

class Graph {
    
    private:
    int n;
    unordered_map<int, unordered_map<int, double>> adj_list;
    set<int> seen_vertices;
    vector<double> distances;
    vector<int> prev_verts;

    public:
    
    Graph() {}
    
    Graph (int n) : n(n) {
        vector<double> temp2(n, __DBL_MAX__);
        distances = temp2;
        distances[0] = 0.0;
        vector<int> temp3(n, -1);
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

    int get_prev_index(int v) const { return prev_verts[v]; }

    void set_prev(int i, int j) { prev_verts[i] = j; }

    double edge_weight(int i, int j) {

        if (!adj_list[i].size()) return 0;
        if (adj_list[i].find(j) == adj_list[i].end()) return 0;
        return adj_list[i][j];
        
    }

    void add_seen_vertex(int v) {
        seen_vertices.insert(v);
    }

    void initialize_adjacency_list(int dimension, double max_edge_weight) {
        
        if (dimension == 0)  {

            for (int i = 0; i < n; i++) {
                for (int j = i+1; j < n; j++) {
                    double potentialEdge = uniformDistribution(generator);
                    if (potentialEdge < (128.0/n * .05)) {
                        adj_list[i][j] = potentialEdge;
                        adj_list[j][i] = potentialEdge;
                    }
                }
            }
        }

        else {

            // Generate points
            vector<vector<double>> verts(n, vector<double>(dimension));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < dimension; ++j) {
                    verts[i][j] = uniformDistribution(generator);
                }
            }

            // Feed vertices into KD Tree
            KDTree tree(verts);
            vector<size_t> neighbors;
            for (int i = 0; i < n; ++i) {
                neighbors = tree.neighborhood_indices(verts[i], max_edge_weight);
                for (const size_t ind : neighbors) {
                    double weight = euclideanDistance(verts[i], verts[ind]);
                    adj_list[i][ind] = weight;
                    adj_list[ind][i] = weight;
                }
            }
        }
    }

    double max_edge_weight(int dimension) {

        if (dimension == 0) {
            return 8*(pow(n,-1));
        }
        if (dimension == 2) {
            return 2*(pow(n,-.5));
        }
        if (dimension == 3) {
            return 1.5*(pow(n,-1.0/3.0));
        }
        if (dimension == 4) {
            return 1.4*(pow(n,-1.0/4.0));
        }

        return 0;
    }
};