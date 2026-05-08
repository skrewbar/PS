#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

constexpr int INF = 2e9;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> sorted(a);
    sort(all(sorted));

    int answer = INF;
    for (int i = 0; i < n; i++) {
        if (a[i] == sorted[i])
            continue;

        auto [small, large] = minmax(a[i], sorted[i]);
        int m = max({
            small - sorted.front(),
            sorted.back() - large,
            min(large - sorted.front(), sorted.back() - small)
        });
        minimize(answer, m);
    }

    cout << (answer == INF ? -1 : answer) << '\n';
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