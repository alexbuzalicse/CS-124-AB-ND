#include "graph.hpp"
#include "heap.hpp"

double mstSum(const vector<vector<int>> &mstEdges, const vector<vector<double>> &adjacencyMatrix) {
    
    double sum = 0;

    for (int i = 0; i < mstEdges.size(); i++) {
        sum += adjacencyMatrix[mstEdges[i][0]][mstEdges[i][1]];
    }
    return sum;
}

void tester_func(int dimension, int n) {
    // Generate adjacency matrix
    vector<vector<double>> adjacencyMatrix = getAdjacencyMatrix(dimension, n);

    // Prim
    vector<int> heap = createHeap();
    vector<double> d (n, inf);
    vector<int> S (n, 0);
    vector<int> prev (n,0);
    vector<int> verticesInHeap (n, -1);

    int start = 1;
    heapInsert(heap, d, start, verticesInHeap);

    while (heap.size() != 0) {
        printHeap(heap);
        for (int k = 0; k < n; k++) {cout << S[k] << " ";}
        cout << "\n";
        for (int k = 0; k < n; k++) {cout << verticesInHeap[k] << " ";}
        cout << "\n\n";

        int u = deleteMin(heap, d, verticesInHeap);
        S[u] = 1;

        for (int v = 0; v < n; v++) {
            
            if (v != u && S[v] == 0) {

                double w = adjacencyMatrix[u][v];
                if (d[v] > w) {
                    
                    d[v] = w;
                    prev[v] = u;
                    
                    if (verticesInHeap[v] < 0) {
                        heapInsert(heap, d, v, verticesInHeap); 
                    }
                    else {
                        heap.erase(heap.begin() + verticesInHeap[v]);
                        heapInsert(heap, d, v, verticesInHeap);
                    } 
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i!= start) {
            cout << "(" << prev[i] << ", " << i << ") \n";
        }
    }

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
    g.initialize_adjacency_list(dimension);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << g.edge_weight(i,j) << " ";
        }
        cout << "\n";
    }

    cout << "success!" << endl;

    return 0;
}

