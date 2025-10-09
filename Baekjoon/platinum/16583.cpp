#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<tuple<int, int, int>> boomerangs;

vector<int> adj[101010];
int level[101010], parent[101010], childCnt[101010];

void dfs(int node, bool isRoot, vector<bool>& visited) {
    visited[node] = true;

    int prev = -1;
    for (int child : adj[node]) {
        if (child == parent[node])
            continue;

        if (not visited[child]) {
            level[child] = level[node] + 1;
            parent[child] = node;
            dfs(child, false, visited);
        } else if (level[child] < level[node])
            continue;

        if (childCnt[child] & 1 and parent[child] == node)
            continue;

        childCnt[node]++;

        if (prev == -1) {
            prev = child;
            continue;
        }
        boomerangs.emplace_back(prev, node, child);
        prev = -1;
    }

    if (not isRoot and prev != -1)
        boomerangs.emplace_back(prev, node, parent[node]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    boomerangs.reserve(M >> 1);
    vector<bool> visited(N + 1);
    for (int i = 1; i <= N; i++)
        if (not visited[i])
            dfs(i, true, visited);

    cout << boomerangs.size() << '\n';
    for (auto [i, j, k] : boomerangs)
        cout << i << ' ' << j << ' ' << k << '\n';

    return 0;
}