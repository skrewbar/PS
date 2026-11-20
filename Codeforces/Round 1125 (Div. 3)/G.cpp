#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) { iota(parent.begin(), parent.end(), 0); }

    int getParent(int x) {
        if (x == parent[x]) return x;
        return parent[x] = getParent(parent[x]);
    }

    void unionParent(int u, int v) {
        u = getParent(u);
        v = getParent(v);

        if (u != v) parent[v] = u;
    }

    bool isConnected(int u, int v) { return getParent(u) == getParent(v); }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    ll profit = 0;

    vector<tuple<ll, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;

        edges.emplace_back(d, u, v);
    }
    sort(edges.begin(), edges.end());

    ll components = n;
    DisjointSet ds(n + 1);
    vector<ll> remainEdges;
    for (auto [d, u, v] : edges) {
        if (ds.isConnected(u, v)) {
            profit += d;
            continue;
        }

        ds.unionParent(u, v);
        remainEdges.push_back(d);
        components -= 1;
    }

    vector<ll> suffSum(remainEdges.size() + 1);
    for (int i = remainEdges.size() - 1; i >= 0; i--) {
        suffSum[i] = remainEdges[i] + suffSum[i + 1];
    }

    while (q--) {
        ll x;
        cin >> x;

        int lo = 0, hi = remainEdges.size();
        while (lo < hi) {
            ll mid = (lo + hi) / 2;

            ll cost = (remainEdges.size() - mid + components - 1) * x;
            if (remainEdges[mid] < cost) lo = mid + 1;
            else hi = mid;
        }

        ll ans = profit - components * (components - 1) / 2 * x;
        ll cnt = remainEdges.size() - lo;
        ans += suffSum[lo] - cnt * (2 * components - 1 + cnt) / 2 * x;

        cout << ans << ' ';
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
