#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);

    vector<int> subMax, dp, dpSum;
    subMax = dp = dpSum = vector<int>(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxLeaf = 0;
    auto calcValues = [&](auto self, int v, int p) -> void {
        subMax[v] = 0;

        for (int c : adj[v]) {
            if (c == p) continue;

            self(self, c, v);
            subMax[v] = max({subMax[v], subMax[c], c});
        }

        if (adj[v].size() == 1) maxLeaf = max(maxLeaf, v);
    };
    calcValues(calcValues, n, 0);

    dp[maxLeaf] = dpSum[maxLeaf] = 1;

    for (int i = maxLeaf + 1; i < n; i++) {
        dpSum[i] = dpSum[i - 1];
        if (subMax[i] > i) continue;

        dp[i] = (dpSum[i - 1] - dpSum[subMax[i]]) % MOD;
        dpSum[i] = (dpSum[i] + dp[i]) % MOD;
    }

    vector<int> pref, suff;
    int childCnt = adj[n].size();
    pref = suff = vector<int>(childCnt);
    for (int i = 0; i < childCnt; i++) {
        int c = adj[n][i];
        pref[i] = max({i > 0 ? pref[i - 1] : 0, subMax[c], c});
    }
    for (int i = childCnt - 1; i >= 0; i--) {
        int c = adj[n][i];
        suff[i] = max({i + 1 < childCnt ? suff[i + 1] : 0, subMax[c], c});
    }

    ll ans = dp[n];
    for (int i = 0; i < childCnt; i++) {
        int exMax =
            max(i > 0 ? pref[i - 1] : 0, i + 1 < childCnt ? suff[i + 1] : 0);

        auto calcAns = [&](auto self, int v, int p) -> void {
            if (exMax < v) ans = (ans + dp[v]) % MOD;

            for (int c : adj[v]) {
                if (c == p) continue;
                self(self, c, v);
            }
        };

        calcAns(calcAns, adj[n][i], n);
    }

    cout << (ans + MOD) % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}