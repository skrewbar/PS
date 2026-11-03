#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll INF = 2e9;

struct Edge {
    int to;
    ll t, h;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v; ll t, h;
        cin >> u >> v >> t >> h;

        adj[u].emplace_back(v, t, h);
        adj[v].emplace_back(u, t, h);
    }

    vector<ll> maxTime(n + 1, -INF);
    maxTime[1] = INF;

    priority_queue<pair<ll, int>> pq;
    pq.emplace(INF, 1);

    while (not pq.empty()) {
        auto [safeT, c] = pq.top();
        pq.pop();

        if (safeT < maxTime[c]) continue;

        for (auto [to, t, h] : adj[c]) {
            ll arrT = safeT;
            if (arrT > h) arrT = h;

            ll nxtT = arrT - t;
            if (maxTime[to] < nxtT) {
                maxTime[to] = nxtT;
                pq.emplace(maxTime[to], to);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (maxTime[i] < 0) cout << 0;
        else cout << 1;
    }

    return 0;
}
