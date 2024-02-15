#include "algos.hpp"

double mstSum(const vector<vector<int>> &mstEdges, const vector<vector<double>> &adjacencyMatrix) {
    
    double sum = 0;

    for (int i = 0; i < mstEdges.size(); i++) {
        sum += adjacencyMatrix[mstEdges[i][0]][mstEdges[i][1]];
    }
    return sum;
}

void graph_tester() {
    Graph g(50);
    // vector<int> adj = g.get_adj_list();
    // cout << "list size is " << adj.size() << endl;
}

int main(int argc, char* argv[])
{
    int n;
    int dimension;
    if (argc > 1)  {
        // Get command line arguments
        int flexibleFlag = stoi(argv[1]);
        n = stoi(argv[2]);
        int m = 65536;
        int trials = stoi(argv[3]);
        dimension = stoi(argv[4]);
        // tester_func(dimension, n);
    }  

    Graph g(n);
    g.insert_custom_edge(0, 1, 1);
    g.insert_custom_edge(1, 2, 2);
    g.insert_custom_edge(2, 3, 3);
    g.insert_custom_edge(0, 3, 4);
    g.insert_custom_edge(0, 2, 5);
    g.insert_custom_edge(1,3, 6);
    
    Heap heap = Heap(4);
    run_prim(g, heap);
    cout << sum_edges(g);

    return 0;
}

