#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj, prev;
    adj = prev = vector(N + 1, vector<int>());

    while (M--) {
        int u_i, v_i;
        cin >> u_i >> v_i;

        adj[u_i].push_back(v_i);
        adj[v_i].push_back(u_i);
    }

    vector<int> dist(N + 1, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (int next : adj[now]) {
            if (dist[next] == -1) {
                dist[next] = dist[now] + 1;
                q.push(next);
            }
            if (dist[next] == dist[now] + 1)
                prev[next].push_back(now);
        }
    }

    vector<bool> visited(N + 1);
    visited[N] = true;
    for (int s : prev[N]) {
        visited[s] = true;
        q.push(s);
    }
    while (not q.empty()) {
        int now = q.front();
        q.pop();

        if (q.empty()) {
            cout << now;
            return 0;
        }

        for (int next : prev[now]) {
            if (visited[next])
                continue;
            visited[next] = true;
            q.push(next);
        }
    }

    assert(false);
}