#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

vector<int> filePrefSum;
vector<vector<int>> dp, opt;

void solve() {
    int n;
    cin >> n;
    filePrefSum.assign(n + 1, 0);
    dp = opt = vector(n + 1, vector(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        cin >> filePrefSum[i];
        filePrefSum[i] += filePrefSum[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        dp[i - 1][i] = 0;
        opt[i - 1][i] = i;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len;
            dp[i][j] = INF;

            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                int cost =
                    dp[i][k] + dp[k][j] + filePrefSum[j] - filePrefSum[i];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    opt[i][j] = k;
                }
            }
        }
    }

    cout << dp[0][n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}