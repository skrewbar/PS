#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

struct Storage {
    ll x, w;
} storages[5050];

ll dist[5050][5050], cost[5050][5050], dp[2][5050];

void dnc(int t, int s, int e, int l, int r) {
    if (s > e)
        return;

    int m = (s + e) >> 1;
    int opt = l;
    dp[t & 1][m] = dp[~t & 1][opt - 1] + cost[opt][m];
    for (int i = l; i <= min(m, r); i++) {
        ll v = dp[~t & 1][i - 1] + cost[i][m];
        if (v < dp[t & 1][m]) {
            dp[t & 1][m] = v;
            opt = i;
        }
    }

    dnc(t, s, m - 1, l, opt);
    dnc(t, m + 1, e, opt, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> storages[i].x >> storages[i].w;
    sort(storages + 1, storages + n + 1,
         [](const Storage& s1, const Storage& s2) { return s1.x < s2.x; });

    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= 1; j--)
            dist[i][j] = dist[i][j + 1] +
                         (storages[i].x - storages[j].x) * storages[j].w;
        for (int j = i + 1; j <= n; j++)
            dist[i][j] = dist[i][j - 1] +
                         (storages[j].x - storages[i].x) * storages[j].w;
    }

    for (int i = 1; i <= n; i++) {
        int opt = i;
        for (int j = 1; j <= n; j++) {
            while (opt < j and dist[opt][i] + dist[opt][j] >
                                   dist[opt + 1][i] + dist[opt + 1][j])
                opt++;
            cost[i][j] = dist[opt][i] + dist[opt][j];
        }
    }

    for (int i = 1; i <= n; i++)
        dp[1][i] = cost[1][i];
    for (int t = 2; t <= k; t++)
        dnc(t, 1, n, 1, n);

    cout << dp[k & 1][n];

    return 0;
}