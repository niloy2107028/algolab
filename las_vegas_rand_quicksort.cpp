#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding random number generator

using namespace std;

// Function to partition the array
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choosing the last element as the pivot
    int i = low - 1;       // Index of the smaller element

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]); // Swap smaller element with arr[j]
        }
    }
    swap(arr[i + 1], arr[high]); // Move pivot to the correct position
    return i + 1;                // Return pivot index
}

// Function to randomize the pivot
int randomizedPartition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1); // Generate random pivot index
    swap(arr[randomIndex], arr[high]);                // Swap it with the last element
    return partition(arr, low, high);                 // Partition the array
}

// Recursive QuickSort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high); // Randomized partition
        quickSort(arr, low, pivotIndex - 1);                  // Sort left subarray
        quickSort(arr, pivotIndex + 1, high);                 // Sort right subarray
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1); // Perform randomized QuickSort

    cout << "Sorted array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


/*

Enter the number of elements: 6
Enter the elements:
3 6 8 10 1 2


Sorted array:
1 2 3 6 8 10


*/