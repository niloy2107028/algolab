#include <iostream>
#include <vector>
#include <limits>
#include <queue>

/*

Bellman ford algorithm for detecting negative cycle and using bfs dfs find sources to the cycle

input:

negative cycle
6 6
4 3 1
3 1 1
1 2 -2
2 5 -3
5 1 -5
2 6 1

no negative cycle
6 6
4 3 1
3 1 1
1 2 -2
2 5 3
5 1 3
2 6 1

*/

using namespace std;

struct edge
{
    int start;
    int end;
    int weight;
};

bool source_to_cycle(vector<int> cycle, vector<vector<int>> graph, int source, int no_of_vertex)
{
    bool result = false;
    for (int i = 0; i < cycle.size(); i++)
    {
        if (cycle[i] == source)
        {
            result = true;
            break;
        }
    }

    if (result == true)
    {
        return result;
    }
    else
    {

        vector<bool> visited(no_of_vertex, false);
        queue<int> queue;
        vector<bool> in_cycle(no_of_vertex, false);

        for (const auto &p : cycle)
        {
            in_cycle[p] = true;
        }

        visited[source] = true;
        queue.push(source);

        while (!queue.empty() && result == false)
        {
            int cur = queue.front();
            queue.pop();

            for (int i = 0; i < graph[cur].size(); i++)
            {

                if (visited[graph[cur][i]] == true)
                {
                    continue;
                }
                else if (in_cycle[graph[cur][i]] == true)
                {
                    result = true;
                    break;
                }
                else
                {
                    queue.push(graph[cur][i]);
                    visited[graph[cur][i]] = true;
                }
            }
        }

        return result;
    }
}

void Bellmen(vector<edge> edges, int no_of_vertex, int no_of_edges, int source, vector<vector<int>> graph)
{
    vector<int> distance(no_of_vertex, numeric_limits<int>::max());
    vector<int> parent(no_of_vertex, 0);

    distance[source] = 0;
    parent[source] = 0;

    for (int i = 0; i < no_of_vertex - 1; i++)
    {
        for (const auto &e : edges)
        {
            if (distance[e.start] != numeric_limits<int>::max() && distance[e.end] > distance[e.start] + e.weight)
            {
                distance[e.end] = distance[e.start] + e.weight;
                parent[e.end] = e.start;
            }
        }
    }

    vector<int> cycle;

    bool negative_cycle = false;

    for (const auto &e : edges)
    {
        if (distance[e.start] != numeric_limits<int>::max() && distance[e.end] > distance[e.start] + e.weight)
        {
            negative_cycle = true;
            int cycle_start = e.start;
            cycle.push_back(cycle_start);
            int temp = parent[e.start];

            while (temp != cycle_start)
            {
                cycle.push_back(temp);
                temp = parent[temp];
            }

            break;
        }
    }

    if (negative_cycle == true)
    {
        cout << "Negative cycle present" << endl;
        cout << "Cycle : ";
        for (int i = cycle.size() - 1; i > -1; i--)
        {
            cout << cycle[i] + 1 << " ";
        }
        cout << endl;

        cout << "Sources that can take you to the cycle : ";

        for (int i = 0; i < no_of_vertex; i++)
        {
            if (source_to_cycle(cycle, graph, i, no_of_vertex))
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "No negative cycle present" << endl;
        cout << "Distance from the source " << source << " : " << endl;
        for (int i = 0; i < distance.size(); i++)
        {
            cout << "distance of " << i + 1 << " : " << (distance[i] == numeric_limits<int>::max() ? -1 : distance[i]) << endl;
        }
    }
}

void show_graph(vector<vector<int>> graph)
{
    cout << "Printing graph : " << endl;
    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << graph[i][j] + 1 << " ";
        }
        cout << endl;
    }
}

int main()

{
    int no_of_edges = 0;
    int no_of_vertex = 0;
    cin >> no_of_edges;
    cin >> no_of_vertex;
    vector<edge> edges(no_of_edges, {0, 0, 0});

    for (size_t i = 0; i < no_of_edges; i++)
    {
        cin >> edges[i].start >> edges[i].end >> edges[i].weight;
        edges[i].start--;
        edges[i].end--;
    }

    vector<vector<int>> graph(no_of_vertex);

    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].push_back(i);
    }

    // cout << "check" << graph.size() << endl;

    for (const auto i : edges)
    {
        graph[i.start].push_back(i.end);
    }

    // show_graph(graph);

    Bellmen(edges, no_of_vertex, no_of_edges, 4 - 1, graph);

    return 0;
}