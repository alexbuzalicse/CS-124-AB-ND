#include <iostream>
#include<vector>
#include<cmath>
#include<limits>

using std::vector;
using std::cout;
using std::swap;
using std::numeric_limits;
using std::pair;
using std::min;

double inf = numeric_limits<double>::infinity();

int parent(int v) {
    return floor((v-1)/2);
}

int left(int v) {
    return (2*v) + 1;
}

int right(int v) {
    return (2*v) + 2;
}

class Heap {
    // implicitly a min heap
    private:
    // represent the heap with a vector of (dist "d", index of vertex)
    vector<pair<double, int>> heap;

    public:
    // default constructor
    Heap () {}

    // default destructor
    ~Heap () {}

    Heap (vector<pair<double, int>> &heap) : heap(heap) {
        this->buildHeap();
    }

    void buildHeap() {
        for (int i = heap.size() / 2; i >= 0; --i) {
            this->minHeapify(i);
        }
    }

    void print() const {
        for (const pair<double, int> &p : heap) {
            cout << p.first << " ";
        }
        cout << endl;
    }

    void minHeapify(int n) {
        int l = left(n), r = right(n);
        int smallest;

        if (l >= 0 && heap[l].first < heap[n].first) smallest = l;
        else smallest = n;
        if (r < heap.size() && heap[r].first < heap[n].first) smallest = r;

        if (smallest != n) {
            int temp = heap[n].first;
            heap[n].first = heap[smallest].first;
            heap[smallest].first = temp;
            this->minHeapify(smallest);
        }
    }

    pair<int, int> top() const { return heap[0]; }

    void push(const pair<double, int> &new_pair) {
        heap.push_back(new_pair);
        int n = heap.size() - 1;

        while (n > 0 && heap[parent(n)] > heap[n]) {
            swap(heap[parent(n)], heap[n]);
            n = parent(n);
        }
    }

    pair<double, int> pop() {
        int n = heap.size();
        pair<double, int> min = heap[0];

        heap[0] = heap[n-1];
        heap.pop_back();
        this->minHeapify(0);

        return min;
    }

    bool empty() const { return heap.size() == 0; }

    // let us index a Heap object outside of the class def
    pair<double, int>& operator[](int index) { return heap[index]; }

};


vector<int> createHeap() {
    return vector<int>{};
}

void printHeap(vector<int> heap) {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << "\n";
}


void heapInsert(vector<int> &heap, vector<double> d, int v, vector<int> &verticesInHeap) {

    heap.push_back(v);
    int N = heap.size() - 1;

    verticesInHeap[v] = N;

    while (N != 0 && d[heap[parent(N)]] > d[heap[N]]) {
        swap(heap[parent(N)], heap[N]);
        swap(verticesInHeap[parent(N)], verticesInHeap[N]);
        N = parent(N);
    }

}

void minHeapify(vector<int> &heap, vector<double> d, int N, vector<int> &verticesInHeap) {

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

int deleteMin(vector<int> &heap, vector<double> d, vector<int> &verticesInHeap) {

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