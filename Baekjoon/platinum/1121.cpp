#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

int len[55];
constexpr int maxLen = 50000;
ll dp[2][11][maxLen + 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> len[i];
    sort(len + 1, len + N + 1);

    int K;
    cin >> K;

    ll ans = 0;

    dp[0][0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = len[i] + 1; j <= maxLen + 1; j++)
            ans += dp[~i & 1][K - 1][j];

        for (int j = 0; j <= K; j++)
            for (int k = 0; k <= maxLen + 1;k ++)
                dp[i & 1][j][k] = dp[~i & 1][j][k];

        for (int j = 1; j <= K; j++) {
            for (int k = 0; k <= maxLen + 1; k++) {
                int lenSum = min(k + len[i], maxLen + 1);
                dp[i & 1][j][lenSum] += dp[~i & 1][j - 1][k];
            }
        }
    }

    cout << ans;

    return 0;
}