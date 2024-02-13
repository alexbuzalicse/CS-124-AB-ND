#include <iostream>
#include<vector>
#include<cmath>
#include<limits>

using std::vector;
using std::cout;
using std::swap;
using std::numeric_limits;

float inf = numeric_limits<float>::infinity();

vector<int> createHeap() {
    return vector<int>{};
}

int parent(int v) {
    return floor((v-1)/2);
}

int left(int v) {
    return (2*v) + 1;
}

int right(int v) {
    return (2*v) + 2;
}

void printHeap(vector<int> heap) {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << "\n";
}

void heapInsert(vector<int> &heap, vector<float> d, int v, vector<int> &verticesInHeap) {

    heap.push_back(v);
    int N = heap.size() - 1;

    verticesInHeap[v] = N;

    while (N != 0 && d[heap[parent(N)]] > d[heap[N]]) {
        swap(heap[parent(N)], heap[N]);
        swap(verticesInHeap[parent(N)], verticesInHeap[N]);
        N = parent(N);
    }

}

void minHeapify(vector<int> &heap, vector<float> d, int N, vector<int> &verticesInHeap) {

    int l = left(N);
    int r = right(N);
    int smallest;

    if (l < heap.size() && d[heap[l]] < d[heap[N]]) {
        smallest = l;
    }

    else {
        smallest = N;
    }

    if (r < heap.size() && d[heap[r]] < d[heap[smallest]]) {
        smallest = r;
    }

    if (smallest != N) {
        swap(heap[N], heap[smallest]);
        swap(verticesInHeap[N], verticesInHeap[smallest]);
        minHeapify(heap, d, smallest, verticesInHeap);
    }
}

int deleteMin(vector<int> &heap, vector<float> d, vector<int> &verticesInHeap) {

    int min = heap[0];
    heap[0] = heap[heap.size() - 1];

    // Update vertex positions in heap
    verticesInHeap[min] = -1;
    for (int i = 0; i < verticesInHeap.size(); i++) {
        if (verticesInHeap[i] >= 0) {
            verticesInHeap[i] -= 1;
        } 
    }

    heap.resize(heap.size() - 1);
    minHeapify(heap, d, 0, verticesInHeap);

    return min;
}