#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> adj[101010];
int color[101010];

void dfs(int cur, int parent) {
    for (auto [child, w] : adj[cur]) {
        if (child == parent) continue;

        if (w % 2 == 0) color[child] = color[cur];
        else color[child] = color[cur] ^ 1;

        dfs(child, cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    dfs(1, -1);

    for (int i = 1; i <= N; i++)
        cout << color[i] << '\n';

    return 0;
}
