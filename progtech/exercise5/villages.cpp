#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    UnionFind uf(N);

    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        uf.unite(A-1, B-1);
    }

    vector<int> groupSizes(N, 0);
    for (int i = 0; i < N; ++i) {
        groupSizes[uf.find(i)]++;
    }

    int initialGroups = count_if(groupSizes.begin(), groupSizes.end(), [](int size) { return size > 0; });
    int remainingGroups = initialGroups - K;
    cout << max(remainingGroups, 1) << endl;

    return 0;
}
