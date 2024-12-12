//The island problem with dfs

#include <bits/stdc++.h>

using namespace std;

void DFS(int **arr, int **visited, int ir, int jc, int n)
{

    if (visited[ir][jc] == 0)
    {
        visited[ir][jc] = 1;
        arr[ir][jc] = 0;

        for (int m = ir - 1; m <= ir + 1; m++)
        {

            for (int k = jc - 1; k <= jc + 1; k++)
            {
                if (arr[m][k] == 1 && visited[m][k] == 0)
                {
                    DFS(arr, visited, m, k, n);
                }
            }
        }
    }
}

int main()

{

    int r, c;
    cin >> r >> c;
    int **arr = new int *[r + 2];      // Dynamically allocate memory for 2D array

    for (int i = 0; i < r + 2; i++)
    {
        arr[i] = new int[r + 2];       // Dynamically allocate memory for each row
        for (int j = 0; j < r + 2; j++)
        {
            arr[i][j] = 0;             // Initialize with zeros
        }
    }

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= r; j++)
        {
            cin >> arr[i][j];
        }
    }

    cout << endl
         << "The map :" << endl
         << endl;

    for (int i = 1; i < r + 1; i++)
    {
        for (int j = 1; j < r + 1; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    // total eight positions : (arr[i-1][j-1]==0&&arr[i-1][j]==0&&arr[i+1][j+1]==0&&arr[i][j-1]==0&&arr[i][j+1]==0&&arr[i+1][j-1]==0
    //&&arr[i+1][j]==0&&arr[i+1][j+1]==0)
    cout << endl;

    int **visited = new int *[r + 2];

    for (int i = 0; i < r + 2; i++)
    {
        visited[i] = new int[r + 2];   // Dynamically allocate memory for each row
        for (int j = 0; j < r + 2; j++)
        {
            visited[i][j] = 0;         // Initialize with zeros
        }
    }

    int island = 0;

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= r; j++)
        {
            if (arr[i][j] == 1 && (arr[i - 1][j - 1] == 0 && arr[i - 1][j] == 0 && arr[i + 1][j + 1] == 0 && arr[i][j - 1] == 0 && arr[i][j + 1] == 0 && arr[i + 1][j - 1] == 0 && arr[i + 1][j] == 0 && arr[i + 1][j + 1] == 0))
            {
                island++;

                arr[i][j] = 0;
            }

            else if (arr[i][j] == 1 && (arr[i - 1][j - 1] == 0 && arr[i - 1][j] == 0 && arr[i][j - 1] == 0 && arr[i - 1][j + 1] == 0))
            {
                island++;

                DFS(arr, visited, i, j, r);
            }
        }
    }

    /*


    cout << "after DFS" << endl;

    for (int i = 1; i < r + 1; i++)
    {
        for (int j = 1; j < r + 1; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    */

    cout << "No of islands here : " << island << endl
         << endl;
    cout << "well termiantion" << endl
         << endl;

    return 0;
}

//sampel inputs and their outputs:

/*

4 4
1 0 1 0
0 0 1 1
1 0 0 1
1 1 0 0

ans:3



4 4
1 0 1 0
0 1 0 1
1 0 1 0
0 1 0 1

ans:1



10 10
0 0 0 0 0 0 0 0 0 0
0 0 1 1 1 1 1 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 0 1 1 1 1 1 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
ans:1

*/
