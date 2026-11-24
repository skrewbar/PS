#include <bits/stdc++.h>
using namespace std;

int parent[100001][20];
int depth[100001];
bool visited[100001];
vector<int> childs[100001];


void dfs(int now) {
    for (int child : childs[now]) {
        if (visited[child]) continue;

        depth[child] = depth[now] + 1;
        visited[child] = true;
        parent[child][0] = now;

        for (int j = 0; j < 20; j++) {
            parent[child][j+1] = parent[parent[child][j]][j];
            if (parent[child][j+1] == 0) break;
        }

        dfs(child);
    }
}


int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    // u is always deeper

    while (depth[u] != depth[v]) {
        int diff = depth[u] - depth[v];

        for (int i = 0; i < 20; i++) {
            if (diff <= 1 << (i+1)) {
                u = parent[u][i];
                break;
            }
        }
    }

    while (u != v) {
        for (int i = 0; i < 20; i++) {
            if (parent[u][i+1] == parent[v][i+1]) {
                u = parent[u][i];
                v = parent[v][i];
                break;
            }
        }
    }

    return u;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        childs[u].push_back(v);
        childs[v].push_back(u);
    }

    visited[1] = true;
    dfs(1);

    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }

    return 0;
}