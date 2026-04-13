#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
 
bool isSafe(vector<int>& board, int row, int col, int N) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col) return false;
        if (abs(board[i]-col) == abs(i-row)) return false;
    }
    return true;
}
 
void solveNQ(vector<int>& board, int row, int N, int& count) {
    if (row == N) {
        count++;
        if (count == 1) {  // Print first solution
            cout << "Solution " << count << ": ";
            for (int c : board) cout << c+1 << " ";
            cout << endl;
            cout << "\nBoard:\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++)
                    cout << (board[i]==j ? "Q " : ". ");
                cout << endl;
            }
        }
        return;
    }
    for (int col = 0; col < N; col++)
        if (isSafe(board, row, col, N)) {
            board[row] = col;
            solveNQ(board, row+1, N, count);
        }
}
 
int main() {
    int N = 4;
    vector<int> board(N, -1);
    int count = 0;
    cout << "N = " << N << endl;
    solveNQ(board, 0, N, count);
    cout << "\nTotal solutions for " << N << "-Queens: " << count << endl;
    return 0;
}
