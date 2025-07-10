#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct DisjointSet {
    vector<int> parent;

    DisjointSet(size_t size) : parent(size) {
        for (int i = 0; i < (int)size; i++)
            parent[i] = i;
    }

    int findParent(int u) {
        if (u != parent[u])
            parent[u] = findParent(parent[u]);
        return parent[u];
    }

    void unionParent(int u, int v) { parent[findParent(u)] = findParent(v); }
};

struct Edge {
    int from, to;
};

void solve(int n, int m, int k) {
    vector<Edge> redEdge, blueEdge;
    for (int i = 0; i < m; i++) {
        Edge edge;
        char color;
        cin >> color >> edge.to >> edge.from;
        if (color == 'B')
            blueEdge.push_back(edge);
        else
            redEdge.push_back(edge);
    }

    int maxBlueEdgeCnt = 0;
    DisjointSet disjointSet(n + 1);
    for (int i = 0; i < (int)blueEdge.size(); i++) {
        Edge edge = blueEdge[i];
        if (disjointSet.findParent(edge.from) ==
            disjointSet.findParent(edge.to))
            continue;
        maxBlueEdgeCnt++;
        disjointSet.unionParent(edge.from, edge.to);
    }

    int minBlueEdgeCnt = n - 1;
    disjointSet = DisjointSet(n + 1);
    for (int i = 0; i < (int)redEdge.size(); i++) {
        Edge edge = redEdge[i];
        if (disjointSet.findParent(edge.from) ==
            disjointSet.findParent(edge.to))
            continue;
        minBlueEdgeCnt--;
        disjointSet.unionParent(edge.from, edge.to);
    }

    print("{}\n", minBlueEdgeCnt <= k and k <= maxBlueEdgeCnt ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    while (n != 0) {
        solve(n, m, k);
        cin >> n >> m >> k;
    }

    return 0;
}