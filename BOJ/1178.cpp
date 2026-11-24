#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> adj[1010];

int getOddCnt(int now, vector<bool>& visited) {
    visited[now] = true;

    int ret = adj[now].size() & 1;

    for (int child : adj[now]) {
        if (visited[child])
            continue;
        ret += getOddCnt(child, visited);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0;
    int componentCnt = 0;

    vector<bool> visited(V + 1);

    for (int i = 1; i <= V; i++) {
        if (visited[i])
            continue;

        componentCnt++;

        int cnt = getOddCnt(i, visited);
        
        if (cnt > 2)
            ans += (cnt - 2) >> 1;
    }

    cout << ans + componentCnt - 1;

    return 0;
}