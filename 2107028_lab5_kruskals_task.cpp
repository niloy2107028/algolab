#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct edge
{
    int u, v, weight;

    bool operator<(const edge &other) const // this function is used to sort the edge array depending on the weights
    {
        return weight < other.weight;
    }
};

class disjointset
{

public:
    vector<int> parent, rank;

    disjointset(int n)
    {
        parent.resize(n);
        rank.resize(n);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV)
            return false;
        if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else
        {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

int kruskal(int n, vector<edge> &edges, vector<edge> &mst)
{
    disjointset ds(n);
    sort(edges.begin(), edges.end());
    int totalweight = 0;

    for (const edge &edge : edges)
    {
        if (ds.unite(edge.u, edge.v))
        {
            totalweight += edge.weight;
            mst.push_back(edge);
            if (mst.size() == n - 1)
                break;
        }
    }

    if (mst.size() != n - 1)
        return -1;
    return totalweight;
}

int secondbestmst(int n, vector<edge> &edges, const vector<edge> &mst, int mstweight)
{
    int secondbestweight = INT_MAX;

    for (int i = 0; i < mst.size(); i++)
    {
        disjointset ds(n);
        int totalweigth = 0, edgeused = 0;

        for (int j = 0; j < edges.size(); j++)
        {
            if (edges[j].u == mst[i].u && edges[j].v == mst[i].v && edges[j].weight == mst[i].weight)
                continue;

            if (ds.unite(edges[j].u, edges[j].v))
            {
                totalweigth += edges[j].weight;
                edgeused++;
                if (edgeused == n - 1)
                    break;
            }
        }

        if (edgeused == n - 1 && totalweigth > mstweight)
        {
            secondbestweight = min(secondbestweight, totalweigth);
        }
    }

    if (secondbestweight == INT_MAX)
        return -1;
    return secondbestweight;
}

int main()

{
    int n, m;
    cin >> n >> m;
    vector<edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--;
        edges[i].v--;
    }

    vector<edge> mst;

    int mstweight = kruskal(n, edges, mst);

    if (mstweight == -1)
    {
        cout << "NO MST exists" << endl;
        return 0;
    }

    int secondmstweight = secondbestmst(n, edges, mst, mstweight);

    cout << mstweight << " " << secondmstweight << endl;

    return 0;
}

/*
4 5
1 2 1
1 3 2
1 4 3
2 3 4
3 4 5

*/