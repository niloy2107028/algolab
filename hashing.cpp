#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

#define MOD 1000000007
#define BASE 31

long long hash_value(const string& s) {
    long long h = 0;
    for (char c : s) {
        h = (h * BASE + (c - 'a' + 1)) % MOD;
    }
    return h;
}

int main() {
    string s, good_chars;
    int k;
    cin >> s >> good_chars >> k;

    int n = s.size();
    vector<bool> is_good(26, false);
    for (int i = 0; i < 26; ++i) {
        is_good[i] = (good_chars[i] == '1');
    }

    unordered_set<long long> good_substrings;
    vector<int> bad_count(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        bad_count[i + 1] = bad_count[i] + (is_good[s[i] - 'a'] ? 0 : 1);
    }

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (bad_count[r + 1] - bad_count[l] <= k) {
                good_substrings.insert(hash_value(s.substr(l, r - l + 1)));
            }
        }
    }

    cout << good_substrings.size() << endl;

    return 0;
}
