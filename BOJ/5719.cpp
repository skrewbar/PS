#include <bits/stdc++.h>
using namespace std;

template <typename T>
using greater_priority_queue = priority_queue<T, vector<T>, greater<T>>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n, m, s, d;
        cin >> n >> m;
        if (n == 0 and m == 0) break;
        cin >> s >> d;
        vector<map<int, int>> adj(n);
        while (m--) {
            int u, v, p;
            cin >> u >> v >> p;
            adj[u][v] = p;
        }

        vector<int> dist(n, INT_MAX);
        vector<vector<int>> path(n);
        dist[s] = 0;
        greater_priority_queue<pair<int, int>> pq;
        pq.emplace(0, s);
        while (not pq.empty()) {
            auto [cur_cost, cur] = pq.top();
            pq.pop();
            if (dist[cur] < cur_cost) continue;

            for (auto [next, adj_cost] : adj[cur]) {
                int next_cost = cur_cost + adj_cost;
                if (next_cost < dist[next]) {
                    dist[next] = next_cost;
                    pq.emplace(dist[next], next);

                    path[next].clear();
                }
                if (next_cost <= dist[next]) {
                    path[next].emplace_back(cur);
                }
            }
        }

        vector<bool> visited(n);
        visited[d] = true;
        queue<int> q;
        q.emplace(d);
        while (not q.empty()) {
            int cur = q.front();
            q.pop();
            for (int next : path[cur]) {
                if (not visited[next]) {
                    visited[next] = true;
                    q.emplace(next);
                }
                adj[next].erase(cur);
            }
        }

        fill(dist.begin(), dist.end(), INT_MAX);
        dist[s] = 0;
        pq = greater_priority_queue<pair<int, int>>();
        pq.emplace(0, s);
        while (not pq.empty()) {
            auto [cur_cost, cur] = pq.top();
            pq.pop();
            if (dist[cur] < cur_cost) continue;

            for (auto [next, adj_cost] : adj[cur]) {
                if (cur_cost + adj_cost < dist[next]) {
                    dist[next] = cur_cost + adj_cost;
                    pq.emplace(dist[next], next);
                }
            }
        }

        cout << (dist[d] == INT_MAX ? -1 : dist[d]) << '\n';
    }
}