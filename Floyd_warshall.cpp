#include <iostream>
#include <vector>
#include <algorithm> // For std::min

using namespace std;

vector<vector<int>> cur_arr;

int no_of_vertex;

void floyd_warshall()
{

    for (size_t k = 1; k < no_of_vertex + 1; k++)
    {
        for (size_t i = 1; i < no_of_vertex + 1; i++)
        {
            for (size_t j = 1; j < no_of_vertex + 1; j++)
            {
        
                cur_arr[i][j] = min(cur_arr[i][j], cur_arr[i][k] + cur_arr[k][j]);   //k er through te distance
            }
        }
    }
}

int main()
{
    cin >> no_of_vertex;

    cur_arr.resize(no_of_vertex + 1, vector<int>(no_of_vertex + 1, 100));


    for (size_t i = 0; i < no_of_vertex + 1; i++)
    {
        for (size_t j = 0; j < no_of_vertex + 1; j++)
        {

            if (i == 0 || j == 0)
            {
                cur_arr[i][j] = i + j - 1;
                continue;
            }
            cin >> cur_arr[i][j];
        }
    }


    floyd_warshall();


    cout << "The shortest path matrix is:" << endl;
    for (size_t i = 0; i < no_of_vertex + 1; i++)
    {
        for (size_t j = 0; j < no_of_vertex + 1; j++)
        {
            if(i==0&&j==0){
                cout<<"* ";
                continue;
            }
            if (cur_arr[i][j] == 100)
            {
                cout << "INF "; //INF to represent large distances
            }
            else
            {
                cout << cur_arr[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}

/*
4
0 3 100 7
8 0 2 100
5 100 0 1
2 100 100 0
*/

/*
answer:
0 3 5 6
5 0 2 3
3 6 0 1
2 5 7 0

*/