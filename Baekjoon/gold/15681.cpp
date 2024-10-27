#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> connected_nodes;
vector<int> dfs_num;
vector<int> max_child;
vector<bool> visited;
int visit_order = 0;


void dfs(int x) {
    dfs_num[x] = ++visit_order;
    for (int child : connected_nodes[x]) {
        if (visited[child]) continue;
        visited[child] = true;
        dfs(child);
    }
    max_child[x] = visit_order;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r, q;
    cin >> n >> r >> q;

    connected_nodes.resize(n+1);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        connected_nodes[u].push_back(v);
        connected_nodes[v].push_back(u);
    }

    dfs_num.resize(n+1);
    max_child.resize(n+1);
    visited.resize(n+1, false);
    visited[r] = true;
    dfs(r);

    while (q--) {
        int u;
        cin >> u;
        cout << max_child[u] - dfs_num[u] + 1 << '\n';
    }
}