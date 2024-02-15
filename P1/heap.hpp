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
    
    // Keep track of where in heap each vertex is, -1 if not in heap
    vector<int> heapVertexPositions;

    public:
    // default constructor
    Heap () {}

    // default destructor
    ~Heap () {}

    Heap (vector<pair<double, int>> &heap) : heap(heap) {
        this->buildHeap();
    }

    Heap (int n) {
        vector<int> temp(n, -1);
        heapVertexPositions = temp;
    }

    void buildHeap() {
        for (int i = heap.size() / 2; i >= 0; --i) {
            this->minHeapify(i);
        }
    }

    int getHeapVertexPosition(int i) {
        return heapVertexPositions[i];
    }

    void print(bool full = false) const {

        if (heap.size() == 0) {cout << "heap empty";}

        for (const pair<double, int> &p : heap) {
            if (full) {
                cout << "(" << p.first << ", " << p.second << ")" << " ";
            }
            else {
                cout << p.first << " ";
            }
            
        }
        cout << endl;
    }

    void set_key(int loc, double dist) {

        if (dist > heap[loc].first) {
            heap[loc].first = dist;
            this->minHeapify(loc); // preserve heap structure
        }
        
        else {
            heap[loc].first = dist;
            siftUp(loc);
        }
    }

    void siftUp(int n) {

        while (n > 0 && heap[parent(n)] > heap[n]) {
            swap(heap[parent(n)], heap[n]);
            swap(heapVertexPositions[heap[parent(n)].second], heapVertexPositions[heap[n].second]);
            n = parent(n);
        }
    }

    void minHeapify(int n) {

        int l = left(n), r = right(n);
        int smallest;

        if (l < heap.size() && heap[l].first < heap[n].first) smallest = l;
        else smallest = n;
        if (r < heap.size() && heap[r].first < heap[smallest].first) smallest = r;
        if (smallest != n) {
            swap(heapVertexPositions[heap[n].second], heapVertexPositions[heap[smallest].second]);
            swap(heap[n], heap[smallest]);
            this->minHeapify(smallest);
        }
    }

    pair<int, int> top() const { return heap[0]; }

    void push(const pair<double, int> &new_pair) {
        heap.push_back(new_pair);
        int n = heap.size() - 1;
        heapVertexPositions[new_pair.second] = n;

        while (n > 0 && heap[parent(n)] > heap[n]) {
            swap(heap[parent(n)], heap[n]);
            swap(heapVertexPositions[heap[parent(n)].second], heapVertexPositions[heap[n].second]);
            n = parent(n);
        }
    }

    pair<int, int> pop() {
        int n = heap.size();
        pair<int, int> min = heap[0];

        heap[0] = heap[n-1];
        heap.pop_back();

        heapVertexPositions[heap[0].second] = 0;
        heapVertexPositions[min.second] = -1;

        this->minHeapify(0);

        return min;
    }

    bool empty() const { return heap.size() == 0; }

    // let us index a Heap object outside of the class def
    pair<double, int>& operator[](int index) { return heap[index]; }

};