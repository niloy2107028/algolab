#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void floyd_warshall(vector<vector<int>> &matrix, int no_of_vertex)
{
    for (int j = 1; j < no_of_vertex + 1; j++)
    {

        for (int i = 1; i < no_of_vertex + 1; i++)
        {
            if (i == j)
            {
                continue;
            }
            for (int k = 1; k < no_of_vertex + 1; k++)
            {
                if (j == k)
                {
                    continue;
                }
                if (matrix[i][k] != 0 && matrix[j][k] != 0 && matrix[i][j])
                {
                    matrix[i][k] = min((matrix[i][k]), matrix[i][j] + matrix[j][k]);
                }
            }
        }
    }
}

void lab4_task(vector<vector<int>> &matrix, int no_of_vertex, int x, int y)
{
    for (int i = 1; i < no_of_vertex + 1; i++)
    {
        for (int j = 1; j < no_of_vertex + 1; j++)
        {
            if (matrix[i][x] != 0 && matrix[x][y] != 0 && matrix[y][j] != 0)
            {
                int path1 = matrix[i][x] + matrix[x][y] + matrix[y][j];
                int path2 = matrix[i][y] + matrix[y][x] + matrix[x][j];
                matrix[i][j] = min(matrix[i][j], min(path1, path2));
            }
        }
    }
}

int main()

{
    int no_of_vertex = 0;
    int no_of_edges = 0;

    cin >> no_of_vertex >> no_of_edges;

    vector<vector<int>> matrix(no_of_vertex + 1, vector<int>(no_of_vertex + 1, 0));

    int u, v, w;

    for (int i = 0; i < no_of_edges; i++)
    {
        cin >> u >> v >> w;
        matrix[u][v] = w;
        matrix[v][u] = w;
    }

    floyd_warshall(matrix, no_of_vertex);

    int x, y;
    cin >> x >> y;

    lab4_task(matrix, no_of_vertex, x, y);

    for (int i = 1; i < no_of_vertex + 1; i++)
    {
        for (int j = 1; j < no_of_vertex + 1; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}