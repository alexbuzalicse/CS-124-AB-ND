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
    // this will change the prev list
    int n = graph.get_size();

    // remember that heap elements are (cost, vertex index)
    heap.push({0,0});

    while (!heap.empty()) {
        pair<double, int> u_pair = heap.top();
        double dist = u_pair.first;
        double u_ind = u_pair.second;

        heap.pop();
        graph.add_seen_vertex(u_ind);

        for (unordered_map<int, double> &weight : graph.get_vertex(u_ind)) {

        }
        

    }
    
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

double prim_MST(int n, int dimension) {
    // returns the weight of the MST via Prim's algorithm
    // (doesnt record any info, just spits out a number)
    Graph graph(n);
    Heap heap;

    // initialize graph weights
    graph.initialize_adjacency_list(dimension);

    run_prim(graph, heap);
    return sum_edges(graph);
}