#include <iostream>

using namespace std;

const int MAX = 20;

bool isSafe(int board[MAX][MAX], int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

bool solveNQueensUtil(int board[MAX][MAX], int row, int n) {
    if (row >= n)
        return true;

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;

            if (solveNQueensUtil(board, row + 1, n))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

void solveNQueens(int n) {
    int board[MAX][MAX] = {0};

    if (solveNQueensUtil(board, 0, n) == false) {
        cout << "Solution does not exist\n";
        return;
    }

    cout << "N-Queens Solution for N = " << n << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << "\n";
    }
}

int main() {
    int n = 4;
    solveNQueens(n);

    return 0;
}