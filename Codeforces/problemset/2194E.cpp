#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

using ll = long long;

constexpr ll INF = 1e16;

vector<vector<ll>> a, dpTo, dpFrom, maxUntilRow, maxUntilCol;

void solve() {
    int n, m;
    cin >> n >> m;

    a = dpTo = dpFrom = maxUntilRow = maxUntilCol =
        vector(n + 5, vector(m + 5, -INF));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    dpTo[1][1] = a[1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            maximize(dpTo[i][j], dpTo[i - 1][j] + a[i][j]);
            maximize(dpTo[i][j], dpTo[i][j - 1] + a[i][j]);
        }
    }
    dpFrom[n][m] = a[n][m];
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            maximize(dpFrom[i][j], dpFrom[i + 1][j] + a[i][j]);
            maximize(dpFrom[i][j], dpFrom[i][j + 1] + a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            maxUntilRow[i][j] = dpTo[i][j] + dpFrom[i][j] - a[i][j];
        }
    }
    maxUntilCol = maxUntilRow;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            maximize(maxUntilRow[i][j], maxUntilRow[i - 1][j]);
            maximize(maxUntilCol[i][j], maxUntilCol[i][j - 1]);
        }
    }

    ll answer = dpTo[n][m];
    int r = n, c = m;
    while (r and c) {
        ll maximum = max({
            dpTo[n][m] - 2*a[r][c],
            maxUntilCol[r + 1][c - 1],
            maxUntilRow[r - 1][c + 1],
        });
        minimize(answer, maximum);

        if (dpTo[r - 1][c] == dpTo[r][c] - a[r][c])
            r--;
        else
            c--;
    }

    cout << answer << '\n';
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