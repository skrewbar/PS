#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool isPerfect(ll x) {
    ll lo = 1, hi = x;

    while (lo < hi) {
        ll m = (lo + hi) / 2;

        if (m < x / m) lo = m + 1;
        else hi = m;
    }

    return x % lo == 0 and x / lo == lo;
}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> sz(n + 1);
    auto preprocess = [&](auto self, int v, int p) -> void {
        sz[v] = 1;

        int *pp = nullptr;  // parent pointer

        for (int &c : adj[v]) {
            if (c == p) {
                pp = &c;
                continue;
            }

            self(self, c, v);
            sz[v] += sz[c];
        }

        if (not pp) return;

        swap(*pp, adj[v].back());
        adj[v].pop_back();
    };
    preprocess(preprocess, 1, 0);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (not isPerfect(a[i])) continue;

        auto comb2 = [&](int v) { return sz[v] * (sz[i] - 1 - sz[v]); };

        ll twoCnt = 0;
        for (int c : adj[i]) twoCnt += comb2(c);
        twoCnt /= 2;

        ll threeCnt = 0;
        for (int c : adj[i])
            threeCnt += (twoCnt - comb2(c)) * sz[c];
        threeCnt /= 3;

        ans += threeCnt + twoCnt;
        ans += (twoCnt + sz[i] - 1) * (sz[1] - sz[i]);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
