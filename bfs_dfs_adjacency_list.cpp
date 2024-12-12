#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Function to perform BFS
void BFS(int start, const vector<vector<int>>& adj) {
    vector<bool> visited(adj.size(), false); // To keep track of visited nodes
    queue<int> q;

    q.push(start);
    visited[start] = true;

    cout << "BFS: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Traverse all neighbors of the current node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    cout << endl;
}

// Function to perform DFS
void DFS(int start, const vector<vector<int>>& adj) {
    vector<bool> visited(adj.size(), false); // To keep track of visited nodes
    stack<int> s;

    s.push(start);

    cout << "DFS: ";
    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            // Traverse all neighbors of the current node
            // Push them onto the stack in reverse order for correct DFS order
            for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int n, m; // Number of nodes and edges
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // Adjacency list (1-based indexing)

    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    BFS(start, adj);
    DFS(start, adj);

    return 0;
}



/*


Enter the number of nodes and edges: 5 6
Enter the edges (u v):
1 2
1 3
2 4
2 5
3 5
4 5
Enter the starting node: 1



BFS: 1 2 3 4 5
DFS: 1 3 5 4 2


*/