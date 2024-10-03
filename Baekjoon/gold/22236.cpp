#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp[4001][4001];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int d, m;
    cin >> d >> m;
    fill(&dp[0][0], &dp[4000][4001], 0);
    dp[1][1] = 1;
    for (int i = 2 ; i < d ; i++) {
        for (int j = 1 ; j <= i ; j++) {
            if (0 < j - 1) dp[i][j] += dp[i-1][j-1] % m;
            if (j + 1 <= d) dp[i][j] += dp[i-1][j+1] % m;
        }
    }

    cout << dp[d-1][1] % m;

    return 0;
}