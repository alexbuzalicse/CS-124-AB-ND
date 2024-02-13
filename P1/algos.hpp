#include"graph.hpp"
#include"heap.hpp"
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

vector<int*> run_prim(Graph &graph, Heap &heap) {
    int n = graph.get_size();
    vector<int*> prev_edges(n);
    // prev_vertex[i] is the previous vertex id for vertex i
    return prev_edges;
}

double sum_edges(const Graph &graph, const vector<int*> &prev_verts) {
    double sum = 0;
    int n = graph.get_size();
    
    for (int i = 0; i < n; ++i) {
        if (!prev_verts[i]) continue;
        int prev = *(prev_verts[i]);
        // search for (i, prev) edge in the graph and get its weight
    }
}

double prim_MST(int n) {
    // returns the weight of the MST via Prim's algorithm
    // (doesnt record any info, just spits out a number)
    Graph graph(n);
    Heap heap;
    vector<int*> prev_verts = run_prim(graph, heap);
    return sum_edges(graph, prev_verts);
}