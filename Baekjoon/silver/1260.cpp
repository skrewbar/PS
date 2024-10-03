#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> nexts;
vector<bool> visited;


void dfs(int node) {
    if (visited[node]) {
        return;
    }

    cout << node << ' ';
    visited[node] = true;
    for (auto next : nexts[node]) {
        dfs(next);
    }
}

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front(); q.pop();

        cout << node << ' ';

        for (auto next: nexts[node]) {
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m, v;
    cin >> n >> m >> v;
    nexts.resize(n+1, {});
    for (int i = 0 ; i < m ; i++) {
        int a, b; cin >> a >> b;
        nexts[a].push_back(b);
        nexts[b].push_back(a);
    }
    for (int i = 1 ; i <= n ; i++) {
        sort(nexts[i].begin(), nexts[i].end());
    }
    visited.resize(n+1, false);
    dfs(v);
    cout << '\n';
    for (int i = 1 ; i <= n ; i++) {
        visited[i] = false;
    }
    bfs(v);


    return 0;
}