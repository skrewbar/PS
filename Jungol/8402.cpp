#include <bits/stdc++.h>
using namespace std;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

using ll = long long;

ll n, r, p;

ll dp[1010101];

ll getDP(ll i) {
    if (dp[i] != LLONG_MAX) return dp[i];
    dp[i] = (i - 1) * p + r;

    for (ll j = 2; j <= i / j; j++) {
        minimize(dp[i], getDP((i + j - 1) / j) + (j - 1) * p + r);
        ll l = (i + j - 1) / j;
        minimize(dp[i], getDP((i + l - 1) / l) + (l - 1) * p + r);
    }

    return dp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r >> p;
    fill(dp, dp + n + 5, LLONG_MAX);
    dp[1] = 0;
    cout << getDP(n);

    return 0;
}
