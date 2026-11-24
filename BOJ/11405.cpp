#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    vector<vector<int>> adj;
    vector<vector<int>> capacity;
    vector<vector<int>> cost;
    vector<vector<int>> flow;
    int source, sink;
    size_t size;

    FlowNetwork(size_t size, int source, int sink)
        : adj(size),
          capacity(size, vector(size, 0)),
          cost(size, vector(size, INF)),
          flow(size, vector(size, 0)),
          source(source),
          sink(sink),
          size(size) {}

    void addEdge(int u, int v, int edgeCapacity, int edgeCost) {
        adj[u].push_back(v);
        adj[v].push_back(u);

        capacity[u][v] = edgeCapacity;
        capacity[v][u] = 0;

        cost[u][v] = edgeCost;
        cost[v][u] = -edgeCost;
    }

    int getMinCostOfMaxFlow() {
        int totalCost = 0;

        vector<int> prev(size);
        vector<int> inQueue(size);
        vector<int> minCost(size);

        while (true) {
            ranges::fill(prev, -1);
            ranges::fill(inQueue, false);
            inQueue[source] = true;
            ranges::fill(minCost, INF);
            minCost[source] = 0;

            queue<int> q;
            q.push(source);

            while (not q.empty()) {
                int cur = q.front();
                q.pop();
                inQueue[cur] = false;

                for (int next : adj[cur]) {
                    if (capacity[cur][next] - flow[cur][next] <= 0)
                        continue;

                    int nextCost = minCost[cur] + cost[cur][next];
                    if (nextCost < minCost[next]) {
                        minCost[next] = nextCost;
                        prev[next] = cur;
                        if (not inQueue[next]) {
                            inQueue[next] = true;
                            q.push(next);
                        }
                    }
                }
            }

            if (prev[sink] == -1)
                break;

            int bottleneck = INF;
            for (int i = sink; i != source; i = prev[i])
                bottleneck =
                    min(bottleneck, capacity[prev[i]][i] - flow[prev[i]][i]);

            for (int i = sink; i != source; i = prev[i]) {
                totalCost += cost[prev[i]][i] * bottleneck;
                flow[prev[i]][i] += bottleneck;
                flow[i][prev[i]] -= bottleneck;
            }
        }

        return totalCost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int source = 0, sink = n + m + 1;
    // 사람 m + 1 ~ m + n
    // 서점 1 ~ m
    FlowNetwork network(n+m+2, source, sink);

    for (int i = m + 1; i <= m + n; i++) {
        int book;
        cin >> book;
        network.addEdge(i, sink, book, 0);
    }
    for (int i = 1; i <= m; i++) {
        int stock;
        cin >> stock;
        network.addEdge(source, i, stock, 0);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + n; j++) {
            int cost;
            cin >> cost;
            network.addEdge(i, j, INF, cost);
        }
    }

    cout << network.getMinCostOfMaxFlow();
    return 0;
}