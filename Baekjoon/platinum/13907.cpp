#include <bits/stdc++.h>
using namespace std;

constexpr int MAX = 1e9;

template <typename T>
using minimumHeap = priority_queue<T, vector<T>, greater<T>>;

struct Edge {
    int end, cost;
};

struct VisitData {
    int cost, edgeCount, vertex;

    auto operator<=>(const VisitData& data) const = default;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    int s, d;
    cin >> s >> d;
    s--, d--;

    vector<vector<Edge>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;

        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    vector<vector<int>> dist(n, vector<int>(n, MAX));
    dist[s][0] = 0;
    minimumHeap<VisitData> pq;
    pq.emplace(0, 0, s);

    while (not pq.empty()) {
        auto [d, edgeCnt, v] = pq.top();
        pq.pop();

        if (dist[v][edgeCnt] < d)
            continue;
        if (edgeCnt + 1 >= n)
            continue;

        for (auto [next, w] : adj[v]) {
            if (d + w < dist[next][edgeCnt + 1]) {
                dist[next][edgeCnt + 1] = d + w;
                pq.emplace(dist[next][edgeCnt + 1], edgeCnt + 1, next);
            }
        }
    }

    cout << *min_element(dist[d].begin(), dist[d].end()) << '\n';
    while (k--) {
        int p;
        cin >> p;

        int answer = MAX;
        for (int i = 0; i < n; i++)
            answer = min(answer, dist[d][i] += p * i);

        cout << answer << '\n';
    }
}