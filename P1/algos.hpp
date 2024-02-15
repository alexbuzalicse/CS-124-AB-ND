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

        pair<double, int> u_pair = heap.pop();
        double dist = u_pair.first;
        int u_ind = u_pair.second;

        graph.add_seen_vertex(u_ind);

        // THOUGHTS: the "selective" implementation for the weights could be
        // easy with this code if we just leave the non-used edges blank
        // for (auto &[out_vertex, weight] : graph.get_vertex(u_ind)) {
        //     cout << out_vertex << ", ";
        //     if (graph.seen_vertex(out_vertex)) continue;
        //     if (graph.get_distance(out_vertex) > weight) {
        //         graph.set_distance(out_vertex, weight);
        //         graph.set_prev(out_vertex, u_ind);

        //         // now either insert or change into the heap
        //         int heap_pos = heap.getHeapVertexPosition(out_vertex);
        //         if (heap_pos == -1) heap.push({weight, out_vertex});
        //         else heap.set_key(heap_pos, weight);
                
        //     } // if 
        // } // for
        for (int out_vertex = 0; out_vertex < n; out_vertex++) {
            
            if (out_vertex == u_ind) continue;

            double weight = graph.edge_weight(u_ind, out_vertex);
            if (weight == 0) continue; // If edge doesn't exist

            if (graph.seen_vertex(out_vertex)) continue;
    
            if (graph.get_distance(out_vertex) > weight) {
                graph.set_distance(out_vertex, weight);
                graph.set_prev(out_vertex, u_ind);

                // now either insert or change into the heap
                int heap_pos = heap.getHeapVertexPosition(out_vertex);
                if (heap_pos == -1) heap.push({weight, out_vertex});
                else heap.set_key(heap_pos, weight);
                
            } // if 
        } // for
    } // while
} // run_prim

double sum_edges(Graph &graph) {
    double total = 0;
    int n = graph.get_size();
    
    for (int i = 0; i < n; ++i) {
        int prev = graph.get_prev_index(i);
        if (prev == -1) continue;
        // want to add the weight of the edge from *prev to i
        total += graph.edge_weight(prev, i);
    }
    return total;
}

double prim_MST(int n, int dimension) {
    // returns the weight of the MST via Prim's algorithm
    // (doesnt record any info, just spits out a number)
    Graph graph(n);
    Heap heap(n);

    // initialize graph weights
    graph.initialize_adjacency_list(dimension);

    run_prim(graph, heap);
    return sum_edges(graph);
}