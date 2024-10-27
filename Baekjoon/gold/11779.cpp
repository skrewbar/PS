#include<bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> next_list(n+1);
    for (int i = 0; i < m; i++) {
        int start, end, cost;
        cin >> start >> end >> cost;

        next_list[start].push_back({end, cost});
    }
    int start, end;
    cin >> start >> end;

    vector<int> dist(n+1, INT_MAX);
    dist[start] = 0;
    vector<int> route(n+1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, start});
    while (not pq.empty()) {
        int now_dist = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (dist[now] < now_dist) continue;

        for (pair<int, int> p : next_list[now]) {
            int next_node = p.first;
            int next_dist = p.second;

            if (now_dist + next_dist < dist[next_node]) {
                dist[next_node] = now_dist + next_dist;
                route[next_node] = now;
                pq.push({dist[next_node], next_node});
            }
        }
    }

    cout << dist[end] << '\n';

    stack<int> ans;
    ans.push(end);
    while (start != end) {
        end = route[end];
        ans.push(end);
    }

    cout << ans.size() << '\n';

    while (not ans.empty()) {
        cout << ans.top() << ' ';
        ans.pop();
    }
}