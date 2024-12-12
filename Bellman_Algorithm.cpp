#include <iostream>
#include <vector>
#include <limits>

// Bellmen_algorithm_for_finding_minimum_distance_among_vertices_in_a_graph_if_negative_cycle_is_not_present_or_vise_versa

// input containing negative cycle    : 5 5 0 1 1 1 -2 2 3 -7 1 2 -5 3 3 1 4
// input containing no negative cycle : 5 5 0 1 1 1 -2 2 1 -7 3 2 -5 3 3 1 4

using namespace std;

struct edge
{
    int start;
    int weight;
    int end;
};

int no_of_edge = 0;
int no_of_vertex = 0;
vector<edge> edge_arr(no_of_edge);

void Bellmen(int source)
{
    vector<int> distance(no_of_vertex, numeric_limits<int>::max());
    distance[source] = 0;
    for (size_t i = 0; i < no_of_vertex - 1; i++)
    {
        for (const auto &edge : edge_arr)
        {
            if (distance[edge.start] != numeric_limits<int>::max() && distance[edge.end] > distance[edge.start] + edge.weight)
            {
                distance[edge.end] = distance[edge.start] + edge.weight;
            }
        }
    }
    bool cycle = false;
    for (const auto &edge : edge_arr)
    {
        if (distance[edge.start] != numeric_limits<int>::max() && distance[edge.end] > distance[edge.start] + edge.weight)
        {
            cycle = true;
            break;
        }
    }
    if (cycle == true)
    {
        cout << "Negative cycle found . So minimum distance can't be found" << endl;
    }
    else
    {
        cout << "No negative cycle found" << endl;
        for (size_t i = 0; i < no_of_vertex; i++)
        {
            cout << "Distance of " << i << " is : " << distance[i] << endl;
        }
    }
}

/*

5 5 0 1 1 1 -2 2 3 -7 1 2 -5 3 3 1 4

*/

int main()

{
    cin >> no_of_vertex >> no_of_edge;
    edge_arr.reserve(no_of_edge);

    // edge_arr.resize(no_of_edge);   resize er sathe cin & reserve er sathe push_back

    // for (size_t i = 0; i < no_of_edge; i++)
    // {
    //     cin >> edge_arr[i].start;
    //     cin >> edge_arr[i].weight;
    //     cin >> edge_arr[i].end;
    // }

    for (size_t i = 0; i < no_of_edge; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge_arr.push_back({a, b, c});
    }

    for (size_t i = 0; i < no_of_edge; i++)
    {
        cout << edge_arr[i].start << " ";
        cout << edge_arr[i].weight << " ";
        cout << edge_arr[i].end << endl;
    }

    Bellmen(0);

    return 0;
}