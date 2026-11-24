#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll a[101010];

ll dp[2][101010];
int opt[222][101010];

ll cost(int l, int r) {
    return (a[r] - a[l - 1]) * a[l - 1];
}

void dnc(int t, int s, int e, int l, int r) {
    if (s > e)
        return;

    int m = (s + e) >> 1;

    dp[t & 1][m] = dp[~t & 1][l - 1] + cost(l, m);
    opt[t][m] = l;
    for (int i = l + 1; i <= min(m, r); i++) {
        ll v = dp[~t & 1][i - 1] + cost(i, m);
        if (v >= dp[t & 1][m]) {
            dp[t & 1][m] = v;
            opt[t][m] = i;
        }
    }

    dnc(t, s, m - 1, l, opt[t][m]);
    dnc(t, m + 1, e, opt[t][m], r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }

    for (int t = 1; t <= k; t++)
        dnc(t, 1, n, 1, n);

    cout << dp[k & 1][n] << '\n';

    int prev = n;
    for (int i = k; i >= 1; i--)
        cout << (prev = opt[i][prev] - 1) << ' ';

    return 0;
}