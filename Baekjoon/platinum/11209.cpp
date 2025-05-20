#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = 1LL << 50;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

int visitedCount = 0;
vector<int> visitOrder;
vector<vector<int>> pathGraph;
vector<bool> isCut;
int getCutPoints(int v) {
    int lowLink = visitOrder[v] = visitedCount++;

    for (int neighbor : pathGraph[v]) {
        if (visitOrder[neighbor] == -1) {
            int childLow = getCutPoints(neighbor);
            if (visitOrder[v] <= childLow)
                isCut[v] = true;

            lowLink = min(lowLink, childLow);
        } else
            lowLink = min(lowLink, visitOrder[neighbor]);
    }

    return lowLink;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    int s, t;
    cin >> s >> t;

    vector<ll> dist(n, INF);
    dist[s] = 0;
    vector<vector<int>> prev(n);
    MinHeap<pair<ll, int>> pq;
    pq.emplace(0, s);
    while (not pq.empty()) {
        auto [curDist, cur] = pq.top();
        pq.pop();
        if (dist[cur] < curDist)
            continue;

        for (auto [next, weight] : adj[cur]) {
            ll nextDist = curDist + weight;
            if (nextDist < dist[next]) {
                prev[next].clear();
                dist[next] = nextDist;
                pq.emplace(nextDist, next);
            }
            if (nextDist <= dist[next])
                prev[next].push_back(cur);
        }
    }

    pathGraph = vector<vector<int>>(n);
    vector<bool> visited(n);
    visited[t] = true;
    queue<int> q;
    q.push(t);
    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (int next : prev[cur]) {
            pathGraph[cur].push_back(next);
            pathGraph[next].push_back(cur);
            if (visited[next])
                continue;
            visited[next] = true;
            q.push(next);
        }
    }

    visitOrder = vector(n, -1);
    isCut = vector(n, false);
    isCut[s] = isCut[t] = true;
    getCutPoints(s);

    for (int i = 0; i < n; i++) {
        if (isCut[i])
            cout << i << ' ';
    }
}