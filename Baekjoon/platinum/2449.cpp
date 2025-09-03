#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int dp[222][222];
// dp[i][j] represents the minimum number of operations needed to make all bulbs
// in [i, j] be the same color

int color[222];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    fill(&dp[0][0], &dp[N][N + 1], N);

    for (int i = 1; i <= N; i++) {
        cin >> color[i];
        dp[i][i] = 0;
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 1; i <= N - len + 1; i++) {
            int j = i + len - 1;

            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] +
                                             (color[i] != color[k + 1]));
            }
        }
    }

    cout << dp[1][N];

    return 0;
}