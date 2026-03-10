#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

struct DisjointSet {
    int n;
    vector<int> parent;

    DisjointSet(int _n) : n(_n), parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findParent(int x) {
        if (x != parent[x])
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u);
        v = findParent(v);

        if (u == v)
            return;

        parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> values;
    values.reserve(2 * n);

    vector<pair<int, int>> plates(n);
    for (auto& [s, t] : plates) {
        cin >> s >> t;
        values.push_back(s);
        values.push_back(t);
    }

    ranges::sort(values);
    values.erase(ranges::unique(values).begin(), values.end());

    vector<vector<int>> adj(values.size());
    for (auto [s, t] : plates) {
        s = ranges::lower_bound(values, s) - values.begin();
        t = ranges::lower_bound(values, t) - values.begin();

        adj[s].push_back(t);
        adj[t].push_back(s);
    }

    vector<bool> visited(values.size());
    int maxWeight = 0;
    ll sum = 0;
    bool hasCycle = false;
    function<void(int, int)> dfs = [&](int cur, int prev) {
        visited[cur] = true;
        sum += values[cur];
        maxWeight = max(maxWeight, values[cur]);

        for (int nxt : adj[cur]) {
            if (nxt == prev) {
                prev = -1;
                continue;
            }

            if (visited[nxt]) {
                hasCycle = true;
                return;
            }

            dfs(nxt, cur);
        }
    };

    ll answer = 0;
    for (auto [s, t] : plates)
        answer += s + t;

    for (int i = 0; i < values.size(); i++) {
        if (visited[i])
            continue;

        maxWeight = 0;
        sum = 0;
        hasCycle = false;
        dfs(i, -1);

        answer -= sum - (hasCycle ? 0 : maxWeight);
    }

    println("{}", answer);

    return 0;
}