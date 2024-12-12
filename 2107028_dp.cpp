#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int mod = 100000007;

int main()

{

    int t;
    cin >> t;

    while (t--)
    {
        int n,k;
        cin >> n >> k;

        vector<int> A(n), C(n);

        for (int i = 0; i < n; i++)
        {
            cin >> A[i];
        }

        for (int i = 0; i < n; i++)
        {
            cin >> C[i];
        }

        vector<int> dp(k + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < n; i++)
        {
            vector<int> new_dp(k + 1, 0);

            for (int j = 0; j <= k; j++)
            {
                if (dp[j] > 0)
                {
                    for (int k = 0; k <= C[i] && j + k * A[i] <= k; ++k)
                    {
                        new_dp[j + k * A[i]] = (new_dp[j + k * A[i]] + dp[j]) % mod;
                    }
                }
            }
            dp = new_dp;
        }

        cout << "Case " << t << ": " << dp[k] << endl;
    }

    return 0;
}