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

void run_prim(Graph &graph, Heap &heap) {
    int n = graph.get_size();
    vector<int*> prev_edges(n);
    // prev_vertex[i] is the previous vertex id for vertex i
}

double sum_edges(Graph &graph) {
    double total = 0;
    int n = graph.get_size();
    
    for (int i = 0; i < n; ++i) {
        int* prev = graph.get_prev_index(i);
        if (!prev) continue;
        // want to add the weight of the edge from *prev to i
        total += graph.edge_weight(*prev, i);
    }
    return total;
}

double prim_MST(int n) {
    // returns the weight of the MST via Prim's algorithm
    // (doesnt record any info, just spits out a number)
    Graph graph(n);
    Heap heap;
    run_prim(graph, heap);
    return sum_edges(graph);
}