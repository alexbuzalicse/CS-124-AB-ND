#include"algos.hpp"

vector<vector<double>> gen_vertices(int n, int dim) {
    vector<vector<double>> verts(n, vector<double>(4));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < dim; ++j) {
            verts[i][j] = uniformDistribution(generator);
        }
    }
    return verts;
}

int main() {
    int n = 260000;
    int dim = 4;
    vector<vector<double>> verts = gen_vertices(n, dim);
    cout << verts[n-1][dim-1] << endl;
    return 0;
}