#include <iostream>
#include <string>

using namespace std;
 
void naiveSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    int found = 0;
 
    cout << "Text    : " << text    << endl;
    cout << "Pattern : " << pattern << endl;
    cout << "\nPattern found at positions: ";
 
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (text[i+j] != pattern[j]) break;
        if (j == m) { cout << i << " "; found++; }
    }
 
    if (found == 0) cout << "(none)";
    cout << endl;
    cout << "Total occurrences: " << found << endl;
}
 
int main() {
    string text    = "AABAACAADAABAABA";
    string pattern = "AABA";
    naiveSearch(text, pattern);
    return 0;
}
