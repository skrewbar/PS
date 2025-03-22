#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    vector<int> indegree(n);

    for (int i = 0; i < m; i++) {
        int departure, arrival, cost;
        cin >> departure >> arrival >> cost;
        departure--, arrival--;

        adj[departure].emplace_back(arrival, cost);
        indegree[arrival]++;
    }

    int departure, arrival;
    cin >> departure >> arrival;
    departure--, arrival--;

    queue<int> q;
    q.push(departure);

    vector<vector<int>> reversePath(n);
    vector<int> maxCost(n);

    // 임계 경로 길이 찾기
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (auto [next, cost] : adj[now]) {
            if (cost + maxCost[now] > maxCost[next]) {
                maxCost[next] = cost + maxCost[now];
                reversePath[next].clear();
                reversePath[next].push_back(now);
            } else if (cost + maxCost[now] == maxCost[next]) {
                reversePath[next].push_back(now);
            }
            indegree[next]--;
            if (indegree[next] == 0) q.push(next);
        }
    }

    // bfs로 임계 경로 도로 수 찾기
    int lineCount = 0;
    vector<vector<bool>> visited(n, vector<bool>(n));
    q = queue<int>();
    q.push(arrival);
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int next : reversePath[now]) {
            if (visited[now][next]) continue;
            visited[now][next] = true;
            q.push(next);
            lineCount++;
        }
    }

    print("{}\n{}", maxCost[arrival], lineCount);
}