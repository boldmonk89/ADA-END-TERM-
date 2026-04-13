#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace chrono;
 
int binarySearch(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
 
int main() {
    vector<int> sizes = {10, 20, 30, 40};
    cout << left << setw(8) << "Size"
         << setw(20) << "Best(ns)"
         << setw(20) << "Average(ns)"
         << setw(20) << "Worst(ns)" << endl;
    cout << string(68, '-') << endl;
 
    for (int n : sizes) {
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
 
        // Best: middle element
        auto s1 = high_resolution_clock::now();
        binarySearch(arr, arr[n/2]);
        auto e1 = high_resolution_clock::now();
        long long best = duration_cast<nanoseconds>(e1-s1).count();
 
        // Worst: element not present
        auto s2 = high_resolution_clock::now();
        binarySearch(arr, n + 100);
        auto e2 = high_resolution_clock::now();
        long long worst = duration_cast<nanoseconds>(e2-s2).count();
 
        cout << setw(8)  << n
             << setw(20) << best
             << setw(20) << (best+worst)/2
             << setw(20) << worst << endl;
    }
    return 0;
}
