#include <bits/stdc++.h>
using namespace std;

int dp[30][30];

int get_case(int n, int m) {
    if (dp[n][m] != -1) return dp[n][m];

    dp[n][m] = 0;
    for (int i = 1; i <= m; i++) {
        dp[n][m] += get_case(n-1, i-1);
    }

    return dp[n][m];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(&dp[0][0], &dp[29][30], -1);
    for (int i = 1; i < 30; i++) {
        dp[1][i] = i;
        dp[i][0] = 0;
    }

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << get_case(n, m) << '\n';
    }
}