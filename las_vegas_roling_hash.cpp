#include <iostream>
#include <string>
using namespace std;

// Function to compute the hash of the first 'm' characters of a string
long long Hash(const string& s, int m, int B, int M) {
    long long h = 0;
    long long power = 1;

    for (int i = m - 1; i >= 0; --i) {
        h = (h + (s[i] * power) % M) % M;
        power = (power * B) % M;
    }

    return h;
}

// Function to find the pattern in the text using the rolling hash algorithm
int Match(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (n < m || m == 0 || n == 0) {
        return -1; // Pattern cannot be found
    }

    const int B = 347;           // Base value for hashing
    const int M = 1000000007;    // Modulus for hashing to prevent overflow

    // Calculate B^(m-1)
    long long power = 1;
    for (int i = 1; i < m; ++i) {
        power = (power * B) % M;
    }

    // Calculate the hash of the first 'm' characters of the text and the pattern
    long long hash_text = Hash(text, m, B, M);
    long long hash_pattern = Hash(pattern, m, B, M);

    // Check for match at the beginning
    if (hash_text == hash_pattern) {
        return 0; // Match found at index 0
    }

    // Rolling hash for the rest of the text
    for (int i = m; i < n; ++i) {
        // Remove the old character
        hash_text = (hash_text - (power * text[i - m]) % M + M) % M;
        // Shift the window
        hash_text = (hash_text * B) % M;
        // Add the new character
        hash_text = (hash_text + text[i]) % M;

        // Check for match
        if (hash_text == hash_pattern) {
            return i - m + 1; // Match found
        }
    }

    return -1; // No match found
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    int result = Match(text, pattern);

    if (result != -1) {
        cout << "Pattern found at index: " << result << endl;
    } else {
        cout << "Pattern not found." << endl;
    }

    return 0;
}
