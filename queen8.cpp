#include <iostream>

using namespace std;

const int numQ=8;

int board[numQ][numQ] = {0};

void displayBoard() {
    static int solutions = 0;
    for (int row=0; row<numQ; ++row) {
        for (int col=0; col<numQ; ++col) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
    cout << ++solutions << endl;
}

bool isSafe(int n, int row, int col) {
    for (int i=row-1; i >= 0; i--) {
        if (board[i][col] == 1) return false;
    }
    for (int i=row-1, j=col-1; i>=0 && j>=0; i--, j--) {
        if (board[i][j] == 1) return false;
    }
    for (int i=row-1, j=col+1; i>=0 && j<n; i--, j++) {
        if (board[i][j] == 1) return false;
    }
    return true;
}

void solve(int n, int row) {
    if (row == n) {
        displayBoard();
        return;
    }
    for (int col=0; col<n; col++) {
        if (isSafe(n,row,col)) {
            board[row][col] = 1;
            solve(n,row+1);
        }
        board[row][col] = 0;
    }
}

int main() {
    solve(numQ,0);
}
