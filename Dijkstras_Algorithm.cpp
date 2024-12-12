#include <iostream>
#include <vector>
#include <limits>

//Dijkstras_algorithm_for_finding_minimum_distance_among_vertices_in_a_graph
//dijkstra will not work for undirected negative edge situation but will work for directed negative edge situation

// demo input 1 (lab slide example) : 7 8 0 1 2 0 2 6 1 3 6 2 3 1 3 4 10 3 5 15 4 6 2 5 6 6
// demo graph 1 :
// here vertices are between braces
/*


      (1)         (4)
     /   \       /   \
   2      6     10    2
  /        \   /       \
(0)         (3)        (6)
  \        /   \       /
   6      1     15    6
     \   /       \   /
      (2)         (5)


*/

// demo input 2 (assignment_1 test case 1): 5 5 0 1 4 0 2 1 1 3 1  2 3 5 3 4 3
// demo graph 2 :
// here vertices are between braces
/*


      (1)         (4)
     /   \       /
   4      1     3
  /        \   /
(0)         (3)
  \        /
   1      5
     \   /
      (2)



*/

using namespace std;

struct paair // it is important for making min heap nodes
{
    int distance_vertex;
    int distance_weight;
};

class Min_Heap
{

public:
    paair arr[100];
    int size;

    Min_Heap()
    {
        size = 0; // index 0 will no be used
        arr[0].distance_vertex = -1;
        arr[0].distance_weight = -1;
    }

    void insert(int D_value, int D_index)
    {
        size = size + 1;
        int index = size;
        arr[index].distance_weight = D_value;
        arr[index].distance_vertex = D_index;

        int parent = 0;
        parent = index / 2;     //1 based

        while (index > 1 && arr[parent].distance_weight > arr[index].distance_weight) // heapify  //parent to 0 
        {

            swap(arr[parent], arr[index]);
            index = parent;
            parent = index / 2;
        }
    }

    void print()
    {
        cout << "Heap elements: ";
        for (int i = 1; i <= size; i++)
        {
            cout << arr[i].distance_weight << "- (" << arr[i].distance_vertex << ") ";
        }
        cout << endl;
    }

    void Delete_Heap()
    {
        if (size == 0)
        {
            cout << "No element to delete" << endl;
            return;
        }
        arr[1] = arr[size];
        size--;
        heapify(1); //                    heapify is necessary after deleting
    }

    void heapify(int i)           //1 to n heapify
    {
        int smallest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= size && arr[left].distance_weight < arr[smallest].distance_weight)
        {
            smallest = left;
        }
        if (right <= size && arr[right].distance_weight < arr[smallest].distance_weight)
        {
            smallest = right;
        }
        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            heapify(smallest);
        }
    }

    bool is_empty()
    {
        return size == 0;
    }

    paair extract_min()
    {
        if (is_empty())
        {
            return {-1, -1};
        }
        else
        {
            paair min_val = arr[1]; // returns and deletes the minimum weight's vertex
            Delete_Heap();
            return min_val;
        }
    }
    void decrease_key(int D_index, int new_value) // this function is used for updating a node in heap and also heapify
    {
        for (int i = 1; i <= size; i++)
        {
            if (arr[i].distance_vertex == D_index)
            {
                arr[i].distance_weight = new_value;
                int parent = i / 2;
                while (i > 1 && arr[parent].distance_weight > arr[i].distance_weight)    //after updating heapify
                {
                    swap(arr[parent], arr[i]);
                    i = parent;
                    parent = i / 2;
                }
                break;
            }
        }
    }
};

class Graph
{
public:
    vector<vector<pair<int, int>>> graph; // making graph using adjacency list    ; first one is weight
    int no_of_vertices;

    Graph(int n)
    {
        no_of_vertices = n;
        graph.resize(no_of_vertices); // allocating storage for list elements
    }

    void Add_edges(int s, int d, int w)
    {
        graph[s].emplace_back(w, d); // it is used for pushing pair in the list
        graph[d].emplace_back(w, s); // as it is a undirected graph so pushing two times
    }
    void Display_graph()
    {
        cout << endl
             << "Displaying the graph : " << endl;
        for (int i = 0; i < graph.size(); i++)
        {
            cout << "Node (" << i << ") : ";
            for (const auto &p : graph[i])
            {
                cout << " --" << p.first << "--> (" << p.second << ")";
            }
            cout << endl;
        }
    }

    void Dijkstras_algorithm(int source)
    {

        vector<bool> visited(no_of_vertices, false);                      // here "initializing visited array with zero" was performed
        vector<int> distance(no_of_vertices, numeric_limits<int>::max()); // here "initializing distance array with max_value or infinity" was performed

        Min_Heap Heap_distance; // making heap

        distance[source] = 0;

        Heap_distance.insert(0, source);

        while (!Heap_distance.is_empty())
        {
            // cout<<"check"<<endl;
            paair current = Heap_distance.extract_min(); // after extracting it will be deleted
            int cur_vertex = current.distance_vertex;

            if (visited[cur_vertex])
            {
                // cout<<"check1"<<endl;

                continue;
            }

            visited[cur_vertex] = true;

            for (const auto &p : graph[cur_vertex])  //auto updating
            {
                int neighbor = p.second;
                int weight = p.first;

                if (!visited[neighbor] && distance[cur_vertex] + weight < distance[neighbor])
                {
                    distance[neighbor] = distance[cur_vertex] + weight;
                    Heap_distance.insert(distance[neighbor], neighbor);     

                    /*
                    heap e insert kora hocceh next jate kothay jete hbe tar jonno,, insert korar por auto value update hbe distance wise heap e ,, kom distance er next node e jabe,, eta min heap / priority queue diye kora jay,, cz priority wise queue update hbe,, ja nirmal stack queue te hoy na 
                    */
                }
            }
        }

        for (int i = 0; i < no_of_vertices; i++)
        {
            if (distance[i] == numeric_limits<int>::max())
                cout << "vertex " << i << " : INF " << endl;
            else
                cout << "vertex " << i << ": Distance " << distance[i] << endl;
        }
    }
};

int main()

{

    int n;
    // cout << "Enter no of vertices : ";
    cin >> n;
    Graph g(n);

    int no_of_edges;
    // cout << "Enter no of edges : ";
    cin >> no_of_edges;

    int source;
    int weight;
    int destination;

    for (int i = 0; i < no_of_edges; i++)
    {
        // cout << "Enter edge " << i + 1 << " (source weight destination) : ";
        cin >> source >> weight >> destination;
        g.Add_edges(source, weight, destination);
    }

    // g.Display_graph();

    g.Dijkstras_algorithm(0); // the starting node can be any node

    // cout << endl << "well termination" << endl;

    return 0;
}