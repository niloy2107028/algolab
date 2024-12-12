#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
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

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int kruskal(int n, vector<Edge>& edges) {
    DSU dsu(n);
    sort(edges.begin(), edges.end());

    int mstWeight = 0;
    vector<Edge> mstEdges;

    for (Edge& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mstWeight += edge.weight;
            mstEdges.push_back(edge);
        }
    }

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge& e : mstEdges) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }

    return mstWeight;
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter the edges (u, v, weight):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    int mstWeight = kruskal(n, edges);
    cout << "Weight of the Minimum Spanning Tree: " << mstWeight << endl;

    return 0;
}

/*
Enter the number of vertices and edges: 4 5
Enter the edges (u, v, weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4


*/

/*

Edges in the Minimum Spanning Tree:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10
Weight of the Minimum Spanning Tree: 19

*/
