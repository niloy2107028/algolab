#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    string good_bad;
    cin >> good_bad;
    long long k;
    cin >> k;

    unordered_set<string> distinct_substrings;
    long long n = s.length();

    for (long long i = 0; i < n; ++i) {
        long long bad_count = 0;
        string current_substring = "";
        for (long long j = i; j < n; ++j) {
            char c = s[j];
            if (good_bad[c - 'a'] == '0') {
                bad_count++;
            }
            if (bad_count > k) {
                break;
            }
            current_substring += c;
            distinct_substrings.insert(current_substring);
        }
    }

    cout << distinct_substrings.size() << endl;
    return  0;
}
