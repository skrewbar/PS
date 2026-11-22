#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll INF = 1LL << 40;

#define all(v) v.begin(), v.end()

template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) { iota(all(parent), 0); }

    int getParent(int x) {
        if (x == parent[x]) return x;
        return parent[x] = getParent(parent[x]);
    }

    void unionParent(int u, int v) {
        u = getParent(u);
        v = getParent(v);

        if (u != v) parent[u] = v;
    }

    bool isConnected(int u, int v) { return getParent(u) == getParent(v); }
};

struct SegmentTree {
    int n;
    vector<pair<ll, ll>> t;

    SegmentTree(int n) : n(n), t(n << 1, {-INF, -INF}) {}

    static pair<ll, ll> merge(pair<ll, ll> a, pair<ll, ll> b) {
        set<ll> values;

        values.insert(a.first);
        values.insert(a.second);
        values.insert(b.first);
        values.insert(b.second);

        pair<ll, ll> ret;
        ret.first = *prev(values.end(), 1);
        ret.second = *prev(values.end(), 2);

        return ret;
    }

    void change(int i, ll v) {
        for (t[i += n] = {v, -INF}; i > 1; i >>= 1) {
            t[i >> 1] = merge(t[i], t[i ^ 1]);
        }
    }

    pair<ll, ll> getRangeMax(int l, int r) {
        pair<ll, ll> ret = {-INF, -INF};

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) ret = merge(ret, t[l++]);
            if (~r & 1) ret = merge(ret, t[r--]);
        }

        return ret;
    }
};

int in[50505], out[50505], sz[50505], top[50505], parent[50505], depth[50505];
vector<int> adj[50505];

void pruneParents(int cur) {
    for (int &child : adj[cur]) {
        if (child == parent[cur]) {
            swap(adj[cur].back(), child);
            adj[cur].pop_back();
            break;
        }
    }

    for (int child : adj[cur]) {
        parent[child] = cur;
        pruneParents(child);
    }
}

void dfs(int cur) {
    sz[cur] = 1;

    for (int child : adj[cur]) {
        depth[child] = depth[cur] + 1;
        dfs(child);
        sz[cur] += sz[child];
    }
}

void buildHLD(int cur) {
    static int visitedCnt = 0;

    in[cur] = visitedCnt++;

    for (int &child : adj[cur]) {
        if (sz[child] > sz[adj[cur].front()]) swap(adj[cur].front(), child);
    }

    for (int child : adj[cur]) {
        top[child] = (child == adj[cur].front() ? top[cur] : child);
        buildHLD(child);
    }

    out[cur] = visitedCnt - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<tuple<ll, int, int>> edges(E);
    for (auto &[w, u, v] : edges) { cin >> u >> v >> w; }
    sort(all(edges));

    int componentCnt = V;
    ll mstCost = 0;
    vector<tuple<ll, int, int>> mst;
    vector<tuple<ll, int, int>> excluded;
    DisjointSet ds(V + 1);
    for (auto [w, u, v] : edges) {
        if (ds.isConnected(u, v)) {
            excluded.emplace_back(w, u, v);
            continue;
        }

        ds.unionParent(u, v);
        mst.emplace_back(w, u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        componentCnt--;
        mstCost += w;
    }

    if (componentCnt > 1) {
        cout << -1;
        return 0;
    }

    pruneParents(1);
    dfs(1);

    top[1] = 1;
    buildHLD(1);

    SegmentTree seg(V);
    for (auto [w, u, v] : mst) {
        if (parent[u] == v) seg.change(in[u], w);
        else seg.change(in[v], w);
    }

    ll ans = INF;
    for (auto [w, u, v] : excluded) {
        pair<ll, ll> maxOnPath = {-INF, -INF};

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            // u is deeper

            maxOnPath = SegmentTree::merge(maxOnPath, seg.getRangeMax(in[top[u]], in[u]));
            u = parent[top[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        // v is deeper
        maxOnPath = SegmentTree::merge(maxOnPath, seg.getRangeMax(in[u] + 1, in[v]));

        ll m = (maxOnPath.first == w ? maxOnPath.second : maxOnPath.first);
        ans = min(ans, mstCost - m + w);
    }

    if (ans >= INF) cout << -1;
    else cout << ans;

    return 0;
}
