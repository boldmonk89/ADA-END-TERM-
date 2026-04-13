#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
 
int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w];
            if (wt[i-1] <= w)
                dp[i][w] = max(dp[i][w], dp[i-1][w-wt[i-1]] + val[i-1]);
        }
 
    // Trace back selected items
    cout << "\nSelected Items (1=taken, 0=skipped): ";
    int w = W;
    vector<int> selected(n, 0);
    for (int i = n; i > 0; i--)
        if (dp[i][w] != dp[i-1][w]) { selected[i-1] = 1; w -= wt[i-1]; }
    for (int s : selected) cout << s << "  ";
    cout << endl;
 
    return dp[n][W];
}
 
int main() {
    vector<int> val = {60, 100, 120};
    vector<int> wt  = {10, 20, 30};
    int W = 50, n = val.size();
 
    cout << "Values : 60  100  120" << endl;
    cout << "Weights: 10   20   30" << endl;
    cout << "Capacity W = " << W << endl;
 
    int maxProfit = knapsack(W, wt, val, n);
    cout << "\nMaximum Profit = " << maxProfit << endl;
    return 0;
}
