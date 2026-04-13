#include <iostream>
#include <vector>

using namespace std;
 
void subsetSum(vector<int>& arr, vector<int>& subset,
               int index, int target, int current) {
    if (current == target) {
        cout << "{ ";
        for (int x : subset) cout << x << " ";
        cout << "}" << endl;
        return;
    }
    for (int i = index; i < (int)arr.size(); i++) {
        if (current + arr[i] <= target) {
            subset.push_back(arr[i]);
            subsetSum(arr, subset, i+1, target, current+arr[i]);
            subset.pop_back();
        }
    }
}
 
int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int target = 6;
    cout << "Set    : { 1 2 3 4 5 }" << endl;
    cout << "Target : " << target << endl;
    cout << "Subsets with sum = " << target << ":" << endl;
    vector<int> subset;
    subsetSum(arr, subset, 0, target, 0);
    return 0;
}
