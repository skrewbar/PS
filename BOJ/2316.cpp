#include <bits/stdc++.h>
using namespace std;

constexpr int source = 0 << 1 | 1, sink = 1 << 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;

    // i번째 정점으로 들어가는 정점: i << 1, 나가는 정점: i << 1 | 1
    vector<vector<int>> capacity(n << 1, vector(n << 1, 1));
    vector<vector<int>> adj(n << 1);
    for (int i = 0; i < n; i++) {
        adj[i << 1].push_back(i << 1 | 1);
        adj[i << 1 | 1].push_back(i << 1);
        capacity[i << 1 | 1][i << 1] = 0;
    }

    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a << 1 | 1].push_back(b << 1);
        adj[b << 1].push_back(a << 1 | 1);

        adj[b << 1 | 1].push_back(a << 1);
        adj[a << 1].push_back(b << 1 | 1);

        capacity[b << 1][a << 1 | 1] = capacity[a << 1][b << 1 | 1] = 0;
    }

    vector<vector<int>> flow(n << 1, vector(n << 1, 0));
    vector<int> prev(n << 1, -1);  // 경로 역추적용 배열
    int totalFlow = 0;
    while (true) {  // 증가 경로가 없을 때 까지
        ranges::fill(prev, -1);
        queue<int> q;
        q.push(source);
        while (not q.empty() and prev[sink] == -1) {
            int now = q.front();
            q.pop();
            for (int next : adj[now]) {
                if (capacity[now][next] - flow[now][next] > 0 and
                    prev[next] == -1) {
                    prev[next] = now;
                    q.push(next);
                }
            }
        }

        if (prev[sink] == -1)
            break;

        for (int node = sink; node != source; node = prev[node]) {
            flow[prev[node]][node] += 1;
            flow[node][prev[node]] -= 1;
        }
        totalFlow++;
    }

    cout << totalFlow;
}