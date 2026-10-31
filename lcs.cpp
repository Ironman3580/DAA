#include <iostream>
#include <cstring>

using namespace std;

void printLCS(char X[], char Y[], int m, int n) {
    int** dp = new int*[m + 1];
    for (int i = 0; i <= m; i++) {
        dp[i] = new int[n + 1];
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } 
            else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } 
            else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int index = dp[m][n];
    char* lcsStr = new char[index + 1];
    lcsStr[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcsStr[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    cout << "String 1: " << X << "\n";
    cout << "String 2: " << Y << "\n";
    cout << "Longest Common Subsequence: " << lcsStr << "\n";

    delete[] lcsStr;
    for (int k = 0; k <= m; k++) {
        delete[] dp[k];
    }
    delete[] dp;
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int m = strlen(X);
    int n = strlen(Y);

    printLCS(X, Y, m, n);

    return 0;
}