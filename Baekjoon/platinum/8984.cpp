#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) v.begin(), v.end()

#define compress(v) \
    sort(all(v));   \
    v.erase(unique(all(v)), v.end())

#define rank(v, x) \
    lower_bound(all(v), x) - v.begin()

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll L;
    cin >> N >> L;

    vector<pair<int, int>> sticks(N);
    vector<ll> values[2];
    values[0].reserve(N);
    values[1].reserve(N);

    for (auto &[t, d] : sticks) {
        cin >> t >> d;

        values[0].push_back(t);
        values[1].push_back(d);
    }
    sort(all(sticks));

    compress(values[0]), compress(values[1]);

    vector<ll> dp[2];
    dp[0] = dp[1] = vector<ll>(N);

    for (auto [t, d] : sticks) {
        int rankT = rank(values[0], t);
        int rankD = rank(values[1], d);

        ll dpT = dp[0][rankT];
        ll dpD = dp[1][rankD];

        maximize(dp[0][rankT], dpD + L + abs(t - d));
        maximize(dp[1][rankD], dpT + L + abs(t - d));
    }

    ll ans = 0;
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < N; i++) {
            maximize(ans, dp[p][i]);
        }
    }

    cout << ans;

    return 0;
}
