#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        pos[b] = i;
    }

    vector<vector<bool>> dp(n + 1, vector<bool>(2));
    dp[0][1] = true;
    for (int i = 1; i <= n; i++) {
        for (int p = 0; p < 2; p++) {
            if (not dp[i - 1][p]) continue;

            if ((n - i + 1) % 2 == 1) {
                if (pos[i] % 2 == p) {
                    dp[i][0] = dp[i][1] = true;
                }
                continue;
            }

            if (pos[i] % 2 == p) dp[i][p ^ 1] = true;
            else dp[i][p] = true;
        }
    }

    if (dp[n][0] or dp[n][1]) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
