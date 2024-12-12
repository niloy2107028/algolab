#include <iostream>

using namespace std;

bool IsValidPosition(int k, int i, int *arr)
{
    for (int j = 0; j < k; j++)
    {
        if (arr[j] == i || abs(i - arr[j]) == abs(k - j))
        { // row er diff and col er diff
            return false;
        }
    }
    return true;
}

void PrintArr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool NQueens(int k, int n, int *arr)
{

    if (k == n) // Solution found, print it and stop further searching
    {
        PrintArr(arr, n);
        return true;
    }
    for (int i = 0; i < n; i++)
    {
        if (IsValidPosition(k, i, arr))
        {
            arr[k] = i;
                if(NQueens(k+1,n,arr)){
                    return true;
                }
        }
    }
    return false;
}

int main()

{
    int n;
    cin >> n;

    int k = 0;

    int arr[n];

    bool SolN = NQueens(k, n, arr);

    if (SolN == 0)
    {
        cout << "no solution" << endl;
    }

    return 0;
}