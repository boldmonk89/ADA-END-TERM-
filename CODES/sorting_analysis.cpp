#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;
using namespace chrono;
 
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
}
 
void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}
 
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j+1] = arr[j]; j--; }
        arr[j+1] = key;
    }
}
 
long long measureTime(void(*sortFn)(vector<int>), vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFn(arr);
    auto end   = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}
 
int main() {
    vector<int> sizes = {10, 20, 30, 40};
    cout << left << setw(6) << "Size"
         << setw(20) << "Bubble(ns)"
         << setw(20) << "Selection(ns)"
         << setw(20) << "Insertion(ns)" << endl;
    cout << string(66, '-') << endl;
    for (int n : sizes) {
        // Worst case: reverse sorted
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
        reverse(arr.begin(), arr.end());
        cout << setw(6) << n
             << setw(20) << measureTime(bubbleSort, arr)
             << setw(20) << measureTime(selectionSort, arr)
             << setw(20) << measureTime(insertionSort, arr) << endl;
    }
    return 0;
}
