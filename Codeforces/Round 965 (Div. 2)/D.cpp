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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> alts(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (u > v) swap(u, v);

        alts[u].push_back(v);
    }

    vector<int> d(n + 1, n + 1);
    d[1] = 0;
    int winBound = 0; // max(v - dist[v])
    for (int s = 1; s < n; s++) {
        cout << (winBound <= s);

        minimize(d[s], d[s - 1] + 1);
        for (int v : alts[s]) {
            minimize(d[v], d[s] + 1);
            maximize(winBound, v - d[v]);
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
