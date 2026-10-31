#include <iostream>

using namespace std;

void printFibonacciSeries(int n) {
    if (n <= 0) return;

    long long* dp = new long long[n];

    dp[0] = 0;
    if (n > 1) {
        dp[1] = 1;
    }

    for (int i = 2; i < n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << "Fibonacci Series (" << n << " terms): ";
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
    }
    cout << "\n";

    delete[] dp;
}

int main() {
    int n = 10;
    printFibonacciSeries(n);

    return 0;
}