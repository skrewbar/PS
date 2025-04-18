#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<vector<int>> parents, minEdges, maxEdges;
vector<int> depth;
vector<bool> visited;

void init(int node) {
    for (auto [child, length] : adj[node]) {
        if (visited[child]) continue;

        visited[child] = true;
        depth[child] = depth[node] + 1;

        parents[child][0] = node;
        minEdges[child][0] = maxEdges[child][0] = length;
        for (int i = 1; i < 18; i++) {
            parents[child][i] = parents[parents[child][i-1]][i-1];
            minEdges[child][i] = min(minEdges[child][i-1], minEdges[parents[child][i-1]][i-1]);
            maxEdges[child][i] = max(maxEdges[child][i-1], maxEdges[parents[child][i-1]][i-1]);
            if (parents[node][i] == 0) break;
        }
        init(child);
    }
}

void solve(int u, int v) {
    int minEdge = 1e7, maxEdge = 0;

    if (depth[u] < depth[v]) swap(u, v);
    // u가 v보다 더 깊음
    while (depth[u] != depth[v]) {
        int diff = depth[u] - depth[v];
        for (int i = 0; i < 18; i++) {
            if (diff & (1 << i)) {
                minEdge = min(minEdges[u][i], minEdge);
                maxEdge = max(maxEdges[u][i], maxEdge);
                u = parents[u][i];
            }
        }
    }

    while (u != v) {
        for (int i = 0; i < 17; i++) {
            if (parents[u][i+1] == parents[v][i+1]) {
                minEdge = min({minEdges[u][i], minEdges[v][i], minEdge});
                maxEdge = max({maxEdges[u][i], maxEdges[v][i], maxEdge});
                u = parents[u][i];
                v = parents[v][i];
                break;
            }
        }
    }

    cout << minEdge << ' ' << maxEdge << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    adj = vector<vector<pair<int, int>>>(n);

    for (int i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    parents = vector(n, vector(18, 0));
    minEdges = vector(n, vector(18, (int)1e7));
    maxEdges = vector(n, vector(18, 0));
    depth = vector(n, 0);
    visited = vector(n, false);

    visited[0] = true;
    init(0);

    int k;
    cin >> k;
    while (k--) {
        int d, e;
        cin >> d >> e;
        d--, e--;
        solve(d, e);
    }
}