#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int u[4040][4040], dp[808][4040];

int cost(int i, int j) {
    return (u[j][j] - u[j][i - 1] - u[i - 1][j] + u[i - 1][i - 1]) / 2;
}

void find(int t, int s, int e, int l, int r) {
    if (s > e)
        return;

    int m = (s + e) >> 1;
    int opt = l;

    dp[t][m] = dp[t - 1][opt - 1] + cost(opt, m);
    for (int i = opt + 1; i <= r; i++) {
        if (dp[t - 1][i - 1] + cost(i, m) < dp[t][m]) {
            dp[t][m] = dp[t - 1][i - 1] + cost(i, m);
            opt = i;
        }
    }

    find(t, s, m - 1, l, opt);
    find(t, m + 1, e, opt, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> u[i][j];
            u[i][j] += u[i][j - 1] + u[i - 1][j] - u[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= N; i++)
        dp[1][i] = cost(1, i);

    for (int t = 2; t <= K; t++)
        find(t, 1, N, 1, N);

    cout << dp[K][N];
    return 0;
}