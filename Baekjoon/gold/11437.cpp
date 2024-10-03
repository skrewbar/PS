#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;
    vector<vector<int>> linked_node(n+1);

    for (int i = 0 ; i < n-1 ; i++) {
        int a, b;
        cin >> a >> b;
        linked_node[a].push_back(b);
        linked_node[b].push_back(a);
    }


    vector<int> parent(n+1);
    vector<int> depth(n+1);
    vector<bool> visited(n+1, false);
    queue<int> q;

    visited[1] = true;
    parent[1] = 1;
    depth[1] = 0;
    q.push(1);
    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (int child : linked_node[cur]) {
            if (visited[child]) continue;

            visited[child] = true;
            parent[child] = cur;
            depth[child] = depth[cur] + 1;
            q.push(child);
        }
    }


    int m;
    cin >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;

        if (depth[x] < depth[y]) swap(x, y);
        while (depth[x] != depth[y]) x = parent[x];

        while (x != y) {
            x = parent[x];
            y = parent[y];
        }

        cout << y << '\n';
    }


    return 0;
}