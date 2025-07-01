#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

vector<vector<pair<int, ll>>> adj;
vector<vector<pair<int, ll>>> sparseTable;
vector<int> depth;
vector<bool> visited;

void setupSparseTable(int u) {
    visited[u] = true;

    for (auto [v, w] : adj[u]) {
        if (visited[v])
            continue;

        depth[v] = depth[u] + 1;
        sparseTable[v][0] = pair(u, w);

        for (int j = 1; j < 20; j++) {
            auto [p, pWeight] = sparseTable[v][j - 1];
            sparseTable[v][j] = pair(sparseTable[p][j - 1].first,
                                     pWeight + sparseTable[p][j - 1].second);
        }

        setupSparseTable(v);
    }
}

int getLCA(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int depthDiff = depth[u] - depth[v];
    for (int i = 0; i < 20; i++) {
        if (depthDiff & (1 << i))
            u = sparseTable[u][i].first;
    }

    if (u != v) {
        for (int i = 19; i >= 0; i--) {
            int nextU = sparseTable[u][i].first,
                nextV = sparseTable[v][i].first;
            if (nextU != nextV)
                u = nextU, v = nextV;
        }
        u = sparseTable[u][0].first;
    }

    return u;
}

ll getCost(int u, int v) {
    ll ret = 0;

    if (depth[u] < depth[v])
        swap(u, v);

    int depthDiff = depth[u] - depth[v];
    for (int i = 0; i < 20; i++) {
        if (depthDiff & (1 << i)) {
            auto [next, weight] = sparseTable[u][i];
            u = next;
            ret += weight;
        }
    }

    if (u != v) {
        for (int i = 19; i >= 0; i--) {
            auto [nextU, uWeight] = sparseTable[u][i];
            auto [nextV, vWeight] = sparseTable[v][i];
            if (nextU != nextV) {
                u = nextU, v = nextV;
                ret += uWeight + vWeight;
            }
        }

        ret += sparseTable[v][0].second + sparseTable[u][0].second;
    }

    return ret;
}

int getKthNode(int u, int v, int k) {
    k--;
    int lca = getLCA(u, v);
    
    if (depth[u] - depth[lca] >= k) {
        for (int i = 0; i < 20; i++) {
            if (k & (1 << i))
                u = sparseTable[u][i].first;
        }
        return u;
    }

    k = (depth[u] - depth[lca]) + (depth[v] - depth[lca]) - k;
    for (int i = 0; i < 20; i++) {
        if (k & (1 << i))
            v = sparseTable[v][i].first;
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.assign(n + 1, vector<pair<int, ll>>());
    sparseTable.assign(n + 1, vector<pair<int, ll>>(20));
    depth.assign(n + 1, 0);
    visited.assign(n + 1, false);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    setupSparseTable(1);

    int m;
    cin >> m;
    while (m--) {
        int q, u, v;
        cin >> q >> u >> v;

        if (q == 1)
            print("{}\n", getCost(u, v));
        else {
            int k;
            cin >> k;
            print("{}\n", getKthNode(u, v, k));
        }
    }

    return 0;
}