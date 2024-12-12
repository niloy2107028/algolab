#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


struct Item {
    int weight;
    int profit;
};


struct Node {
    int level;     
    int profit;   
    int weight;    
    double bound;  

    
    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};


double bound(const Node& u, int n, int m, const vector<Item>& items) {
    if (u.weight >= m) return 0; 

    double bound = u.profit;
    int totalWeight = u.weight;


    for (int i = u.level + 1; i < n && totalWeight + items[i].weight <= m; i++) {
        totalWeight += items[i].weight;
        bound += items[i].profit;
    }


    if (u.level + 1 < n) {
        int remainingWeight = m - totalWeight;
        bound += (double)items[u.level + 1].profit / items[u.level + 1].weight * remainingWeight;
    }

    return bound;
}


int knapsackBranchAndBound(int m, const vector<Item>& items) {
    int n = items.size();


    vector<Item> sortedItems = items;
    sort(sortedItems.begin(), sortedItems.end(), [](Item a, Item b) {
        return (double)a.profit / a.weight > (double)b.profit / b.weight;
    });

    priority_queue<Node> pq;
    Node u, v;

    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, m, sortedItems);
    pq.push(u);

    int maxProfit = 0;


    while (!pq.empty()) {

        if (u.level == n - 1) continue;

        v.level = u.level + 1;
        v.weight = u.weight + sortedItems[v.level].weight;
        v.profit = u.profit + sortedItems[v.level].profit;

        if (v.weight <= m && v.profit > maxProfit) {
            maxProfit = v.profit;
        }

        v.bound = bound(v, n, m, sortedItems);
        if (v.bound > maxProfit) {
            pq.push(v);
        }


        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, m, sortedItems);
        if (v.bound > maxProfit) {
            pq.push(v);
        }
    }

    return maxProfit;
}

int main() {
    int m = 15;  
    vector<Item> items = {{1, 10}, {4, 10}, {6, 12},{9,18}};

    int maxProfit = knapsackBranchAndBound(m, items);
    cout << "Maximum profit: " << maxProfit << endl;

    return 0;
}
