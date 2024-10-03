#include <bits/stdc++.h>
using namespace std;


vector<vector<pair<int, int>>> next_list;
vector<int> dist;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int v, e, k;
    cin >> v >> e >> k;
    k--;
    next_list.resize(v);
    for (int i = 0 ; i < e ; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        next_list[u].push_back({w, v});
    }


    dist.resize(v, INT_MAX);
    dist[k] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});

    while (not pq.empty()) {
        int cur_dist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (pair<int, int> next_pair : next_list[cur]) {
            int next = next_pair.second;
            int next_dist = cur_dist + next_pair.first;

            if (next_dist < dist[next]) {
                dist[next] = next_dist;
                pq.push({next_dist, next});
            }
        }
    }

    for (int i = 0 ; i < v ; i++) {
        if (dist[i] == INT_MAX) cout << "INF\n";
        else cout << dist[i] << '\n';
    }


    return 0;
}