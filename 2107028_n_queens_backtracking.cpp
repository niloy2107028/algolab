#include <iostream>
#include <cmath>
using namespace std;

const int MAX_N = 10;

int x[MAX_N];

bool Place(int k, int i) {
   
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false; 
        }
    }
    return true;
}

void NQueens(int k, int n) {w

    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            x[k] = i;
            if (k == n) {
               
                for (int j = 1; j <= n; j++) {
                    cout << x[j] << " ";
                }
                cout << endl;
            } else {
            
                NQueens(k + 1, n);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    NQueens(1, n);
    return 0;
}
