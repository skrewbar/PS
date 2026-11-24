#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_DIFF = 250'001;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> dp(n, vector<int>(MAX_DIFF, -1));
    dp[0][0] = 0;
    int h;
    cin >> h;
    if (h < MAX_DIFF)
        dp[0][h] = h;

    for (int i = 1; i < n; i++) {
        cin >> h;
        for (int j = 0; j < MAX_DIFF; j++) {
            if (dp[i - 1][j] == -1)
                continue;

            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            int sub = abs(h - j);
            if (sub < MAX_DIFF)
                dp[i][sub] =
                    max(dp[i][sub], dp[i - 1][j] + (j < h ? h - j : 0));
            int add = h + j;
            if (add < MAX_DIFF)
                dp[i][add] = max(dp[i][add], dp[i - 1][j] + h);
        }
    }

    cout << (dp[n - 1][0] ? dp[n - 1][0] : -1);
}