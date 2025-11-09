#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;
ll dp[22][22][22];

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    fill(&dp[0][0][0], &dp[n][n][n + 1], 0);
    dp[1][1][1] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= i; k++) {
                // append smallest stick
                // to the left side
                dp[i + 1][j + 1][k] += dp[i][j][k];

                // to the right side
                dp[i + 1][j][k + 1] += dp[i][j][k];

                // at the middle positions
                dp[i + 1][j][k] += dp[i][j][k] * (i - 1);
            }
        }
    }

    cout << dp[n][l][r] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}