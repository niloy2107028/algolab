#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Edge {
    int u, v, weight;
};

// A structure to represent a node in the priority queue
struct Node {
    int vertex, dist;
    bool operator<(const Node& other) const {
        return dist > other.dist;
    }
};

const int INF = INT_MAX;

void BellmanFord(int V, int E, int src, vector<Edge>& edges, vector<int>& h) {
    h.assign(V, INF);
    h[src] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (auto& edge : edges) {
            if (h[edge.u] != INF && h[edge.u] + edge.weight < h[edge.v]) {
                h[edge.v] = h[edge.u] + edge.weight;
            }
        }
    }
}

void Dijkstra(int V, int src, vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    priority_queue<Node> pq;
    dist.assign(V, INF);
    dist[src] = 0;
    pq.push({src, 0});

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int u = node.vertex;
        int d = node.dist;

        if (d != dist[u]) continue;

        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({v, dist[v]});
            }
        }
    }
}

void Johnson(int V, int E, vector<Edge>& edges) {
    // Add a new vertex 'V' connected to all other vertices with edge weight 0
    for (int i = 0; i < V; ++i) {
        edges.push_back({V, i, 0});
    }

    // Step 1: Run Bellman-Ford to calculate h[] values
    vector<int> h(V + 1);
    BellmanFord(V + 1, E + V, V, edges, h);

    // Remove the added vertex
    edges.pop_back();

    // Step 2: Reweight the graph
    vector<vector<pair<int, int>>> adj(V);
    for (auto& edge : edges) {
        int new_weight = edge.weight + h[edge.u] - h[edge.v];
        adj[edge.u].push_back({edge.v, new_weight});
    }

    // Step 3: Run Dijkstra for each vertex
    for (int u = 0; u < V; ++u) {
        vector<int> dist;
        Dijkstra(V, u, adj, dist);

        // Step 4: Correct the distances
        for (int v = 0; v < V; ++v) {
            if (dist[v] < INF) {
                dist[v] = dist[v] + h[v] - h[u];
            }
            cout << "Shortest path from " << u << " to " << v << ": " << dist[v] << endl;
        }
    }
}

int main() {
    int V = 4, E = 5;  // Number of vertices and edges
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {3, 2, 5}
    };

    Johnson(V, E, edges);

    return 0;
}
