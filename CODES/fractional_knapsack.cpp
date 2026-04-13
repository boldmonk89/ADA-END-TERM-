#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
 
struct Item {
    int weight, value;
    double ratio;
};
 
double fractionalKnapsack(int W, vector<Item>& items) {
    // Sort by value/weight ratio (descending)
    sort(items.begin(), items.end(), [](Item& a, Item& b) {
        return a.ratio > b.ratio;
    });
 
    double maxProfit = 0.0;
    cout << "\nItem Selection Vector (fractions taken):" << endl;
 
    for (auto& item : items) {
        if (W <= 0) { cout << "0.00  "; continue; }
        if (item.weight <= W) {
            cout << "1.00  ";
            maxProfit += item.value;
            W -= item.weight;
        } else {
            double frac = (double)W / item.weight;
            cout << fixed << setprecision(2) << frac << "  ";
            maxProfit += frac * item.value;
            W = 0;
        }
    }
    cout << endl;
    return maxProfit;
}
 
int main() {
    int W = 50;
    vector<Item> items = {{10,60,6.0},{20,100,5.0},{30,120,4.0}};
    // ratio = value/weight
    for (auto& it : items) it.ratio = (double)it.value / it.weight;
 
    cout << "Items: {w=10,v=60}, {w=20,v=100}, {w=30,v=120}" << endl;
    cout << "Knapsack Capacity: " << W << endl;
 
    double profit = fractionalKnapsack(W, items);
    cout << "\nMaximum Profit = " << fixed << setprecision(2) << profit << endl;
    return 0;
}
