#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
 
string lcs(string X, string Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
 
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++)
            if (X[i-1]==Y[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
 
    // Backtrack to find LCS string
    string result = "";
    int i=m, j=n;
    while (i>0 && j>0) {
        if (X[i-1]==Y[j-1]) { result = X[i-1] + result; i--; j--; }
        else if (dp[i-1][j] > dp[i][j-1]) i--;
        else j--;
    }
    cout << "LCS Length   : " << dp[m][n] << endl;
    return result;
}
 
int main() {
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    cout << "String X     : " << X << endl;
    cout << "String Y     : " << Y << endl;
    string seq = lcs(X, Y);
    cout << "LCS Sequence : " << seq << endl;
    return 0;
}
