#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct DisjointSet {
    vector<int> size;
    vector<int> parent;

    DisjointSet(int n) : size(n, 1), parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int getSize(int x) {
        return size[findParent(x)];
    }

    int findParent(int x) {
        if (parent[x] != x)
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u);
        v = findParent(v);

        if (u != v) {
            parent[v] = u;
            size[u] += size[v];
        }
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

struct Edge {
    int u, v, w;

    bool operator<(const Edge& e) const { return w < e.w; }

    bool operator<(int i) const { return w < i; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto& [u, v, w] : edges)
        cin >> u >> v >> w;
    sort(edges.begin(), edges.end());

    int Q;
    cin >> Q;

    vector<int> x(Q), y(Q);
    vector<int> lo(Q, 0), hi(Q, m);
    vector<pair<int, int>> ans(Q);
    vector<queue<int>> queries(m, queue<int>());
    for (int i = 0; i < Q; i++) {
        cin >> x[i] >> y[i];
        int mid = (lo[i] + hi[i]) / 2;
        queries[mid].push(i);
    }

    while (true) {
        bool solved = true;
        for (int i = 0; i < m; i++) {
            if (not queries[i].empty()) {
                solved = false;
                break;
            }
        }
        if (solved)
            break;

        DisjointSet disjointSet(n + 1);
        for (int i = 0; i < m; i++) {
            auto [u, v, w] = edges[i];
            disjointSet.unionParent(u, v);

            while (not queries[i].empty()) {
                int q = queries[i].front();
                queries[i].pop();

                if (lo[q] == hi[q]) {
                    ans[q] = pair(w, disjointSet.getSize(x[q]));
                    continue;
                }

                if (disjointSet.isConnected(x[q], y[q]))
                    hi[q] = i;
                else
                    lo[q] = i + 1;

                int mid = (lo[q] + hi[q]) / 2;
                if (mid == m) {
                    ans[q] = pair(-1, -1);
                    continue;
                }
                queries[mid].push(q);
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        if (ans[i].first != -1)
            println("{} {}", ans[i].first, ans[i].second);
        else
            println("-1");
    }

    return 0;
}