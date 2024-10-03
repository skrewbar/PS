#include <bits/stdc++.h>
using namespace std;

vector<int> next_nodes[100001];
int visited[100001];


void bfs(int start) {
    queue<int> q;
    q.push(start);
    int order = 1;
    visited[start] = order;

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (int next_node : next_nodes[cur]) {
            if (visited[next_node]) continue;
            q.push(next_node);
            visited[next_node] = ++order;
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m, r;
    cin >> n >> m >> r;

    while (m--) {
        int u, v;
        cin >> u >> v;

        next_nodes[u].push_back(v);
        next_nodes[v].push_back(u);
    }

    for (int i = 1 ; i <= n ; i++) {
        sort(next_nodes[i].begin(), next_nodes[i].end(), greater<>());
    }
    bfs(r);

    for (int i = 1 ; i <= n ; i++) {
        cout << visited[i] << '\n';
    }

    return 0;
}