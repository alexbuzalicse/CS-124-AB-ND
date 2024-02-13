#include "graph.cpp"
#include "heap.cpp"

float mstSum(vector<vector<int>> mstEdges, vector<vector<double>> adjacencyMatrix) {
    
    float sum = 0;

    for (int i = 0; i < mstEdges.size(); i++) {
        sum += adjacencyMatrix[mstEdges[i][0]][mstEdges[i][1]];
    }
    return sum;
}

int main(int argc, char* argv[])
{
    // Get command line arguments
    int flexibleFlag = stoi(argv[1]);
    int n = stoi(argv[2]);
    int m = 65536;
    int trials = stoi(argv[3]);
    int dimension = stoi(argv[4]);

    // Generate adjacency matrix
    vector<vector<double>> adjacencyMatrix = getAdjacencyMatrix(dimension, n);

    // Prim
    vector<int> heap = createHeap();
    vector<float> d (n, inf);
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

                float w = adjacencyMatrix[u][v];
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
    return 0;
}