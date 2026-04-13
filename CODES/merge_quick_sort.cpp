#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;
using namespace chrono;
 
// ── Merge Sort ──────────────────────────────────────────
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> L(arr.begin()+l, arr.begin()+m+1);
    vector<int> R(arr.begin()+m+1, arr.begin()+r+1);
    int i=0, j=0, k=l;
    while (i<L.size() && j<R.size())
        arr[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    while (i<L.size()) arr[k++]=L[i++];
    while (j<R.size()) arr[k++]=R[j++];
}
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
 
// ── Quick Sort ──────────────────────────────────────────
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot) swap(arr[++i], arr[j]);
    swap(arr[i+1], arr[high]);
    return i + 1;
}
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}
 
int main() {
    vector<int> sizes = {10, 20, 30, 40};
    cout << left << setw(6) << "Size"
         << setw(20) << "MergeSort(ns)"
         << setw(20) << "QuickSort(ns)" << endl;
    cout << string(46, '-') << endl;
    for (int n : sizes) {
        vector<int> a1(n), a2(n);
        iota(a1.begin(), a1.end(), 1);
        reverse(a1.begin(), a1.end());   // worst for quick
        a2 = a1;
        auto s1=high_resolution_clock::now();
        mergeSort(a1, 0, n-1);
        auto e1=high_resolution_clock::now();
        auto s2=high_resolution_clock::now();
        quickSort(a2, 0, n-1);
        auto e2=high_resolution_clock::now();
        cout << setw(6)  << n
             << setw(20) << duration_cast<nanoseconds>(e1-s1).count()
             << setw(20) << duration_cast<nanoseconds>(e2-s2).count() << endl;
    }
    return 0;
}
