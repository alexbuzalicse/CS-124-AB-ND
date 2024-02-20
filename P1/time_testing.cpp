#include"algos.hpp"

void gen_vertices(int n, int dim) {
    vector<vector<int>> a(n, vector<int>(4));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < dim; ++j) {
            a[i][j] = uniformDistribution(generator);
        }
    }
}

int main() {
    int n = 260000;
    int dim = 4;
    gen_vertices(n, dim);
    return 0;
}