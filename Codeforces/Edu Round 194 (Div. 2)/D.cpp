#include <bits/stdc++.h>
using namespace std;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

int INF = 1e9;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;
    s = '#' + s;

    if (s[1] == '0') {
        cout << -1 << '\n';
        return;
    }

    vector<vector<int>> dp_arr(n + 1, vector<int>(7, INF));
    auto dp = [&](int i, int j) -> int & { return dp_arr[i][j + 3]; };

    for (int j = -3; j <= 3; j++) {
        if (s[1] == '-' and j >= 0) continue;
        if (s[1] == '+' and j <= 0) continue;

        dp(1, j) = abs(j);
    }

    for (int i = 2; i <= n; i++) {
        for (int j = -3; j <= 3; j++) {
            if (s[i] == '-' and j >= 0) continue;
            if (s[i] == '0' and j != 0) continue;
            if (s[i] == '+' and j <= 0) continue;
            for (int k = -3; k <= 3; k++) {
                if (s[i - 1] == '-' and k >= 0) continue;
                if (s[i - 1] == '0' and k != 0) continue;
                if (s[i - 1] == '+' and k <= 0) continue;

                if (j == k) continue;

                minimize(dp(i, j), max(dp(i - 1, k), abs(j - k)));
            }
        }
    }

    int ans = INF;
    for (int j = -3; j <= 3; j++)
        minimize(ans, dp(n, j));

    if (ans == INF) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
