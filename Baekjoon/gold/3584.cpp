#include <bits/stdc++.h>
using namespace std;


void dfs(vector<int> &depth, vector<vector<int>> &childs, int x) {
    for (int child : childs[x]) {
        depth[child] = depth[x] + 1;
        dfs(depth, childs, child);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> depth(n+1);
        vector<int> parent(n+1);
        vector<vector<int>> childs(n+1);

        for (int i = 0; i < n-1; i++) {
            int a, b;
            cin >> a >> b;
            parent[b] = a;
            childs[a].push_back(b);
        }

        int root = 1;
        while (parent[root] != 0) {
            root = parent[root];
        }

        depth[root] = 1;
        dfs(depth, childs, root);

        int u, v;
        cin >> u >> v;
        if (depth[u] < depth[v]) swap(u, v);

        while (depth[u] != depth[v]) {
            u = parent[u];
        }

        while (u != v) {
            u = parent[u];
            v = parent[v];
        }

        cout << u << "\n";
    }
}