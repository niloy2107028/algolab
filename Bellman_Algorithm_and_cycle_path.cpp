#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct edge
{
    int start;
    int end;
    int weight;
};

int no_of_vertex = 0;
int no_of_edges = 0;
vector<edge> edges;

void bellman(int source)
{
    vector<int> distance(no_of_vertex, numeric_limits<int>::max());
    vector<int> parent(no_of_vertex, -1);

    distance[source] = 0;

    for (int i = 0; i < no_of_vertex - 1; i++)
    {
        for (const auto &p : edges)
        {
            if (distance[p.start] != numeric_limits<int>::max() && distance[p.end] > distance[p.start] + p.weight)
            {
                distance[p.end] = distance[p.start] + p.weight;
                parent[p.end] = p.start;
            }
        }
    }

    bool negative_cycle = false;
    for (const auto &p : edges)
    {
        if (distance[p.start] != numeric_limits<int>::max() && distance[p.end] > distance[p.start] + p.weight)
        {
            negative_cycle = true;

            cout << "Negative cycle detected involving edge (" << p.start << ", " << p.end << ")" << endl;

            int cycle_vertex = p.end;
            vector<int> cycle;

            cycle_vertex = parent[cycle_vertex];

            int start_vertex = cycle_vertex;
            do
            {
                cycle.push_back(cycle_vertex);
                cycle_vertex = parent[cycle_vertex];
            } while (cycle_vertex != start_vertex);
            cycle.push_back(start_vertex);

            cout << "Cycle: ";
            for (int i = cycle.size() - 1; i >= 0; i--)
            {
                cout << cycle[i] << " ";
            }
            cout << endl;
            break;
        }
    }

    if (!negative_cycle)
    {

        for (int i = 0; i < no_of_vertex; i++)
        {
            cout << "Distance of " << i << " : " << distance[i] << endl;
        }
    }
}

/*

5
5
0 1 1
1 -2 2
3 -6 1
2 -5 3
2 1 4

*/

int main()
{
    cin >> no_of_vertex >> no_of_edges;
    edges.resize(no_of_edges);

    for (int i = 0; i < no_of_edges; i++)
    {
        cin >> edges[i].start >> edges[i].weight >> edges[i].end;
    }

    for (int i = 0; i < no_of_edges; i++)
    {
        cout << edges[i].start << " " << edges[i].end << " " << edges[i].weight << endl;
    }

    bellman(0);

    return 0;
}
