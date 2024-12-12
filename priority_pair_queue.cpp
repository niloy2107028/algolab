#include <iostream>
#include <queue>
#include <vector>
using namespace std;
 
// Custom comparator for priority queue
struct compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        // Compare based on the first value (priority)
        return a.first < b.first;  // Max-heap: larger first value has higher priority

        //for max heap
        //return a.first>b.first;
    }
};
 
// driver code
int main()
{
    // array of pairs {priority, value}
    pair<int, int> arr[6] = { {10, 100}, {2, 200}, {4, 300}, {8, 400}, {6, 500}, {9, 600} };
 
    // defining priority queue with custom comparator
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
 
    // printing array
    cout << "Array of pairs: ";
    for (auto i : arr) {
        cout << "{" << i.first << ", " << i.second << "} ";
    }
    cout << endl;
 
    // pushing array of pairs sequentially
    for (int i = 0; i < 6; i++) {
        pq.push(arr[i]);
    }
 
    // printing priority queue
    cout << "Priority Queue (ordered by priority): ";
    while (!pq.empty()) {
        cout << "{" << pq.top().first << ", " << pq.top().second << "} ";
        pq.pop();
    }
 
    return 0;
}
