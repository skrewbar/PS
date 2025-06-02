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
          capacity(size, vector<int>(size)),
          cost(size, vector<int>(size)),
          flow(size, vector<int>(size, 0)),
          source(source),
          sink(sink),
          size(size) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void setCapacity(int u, int v, int _capacity) {
        capacity[u][v] = _capacity;
        capacity[v][u] = 0;
    }
    void setCost(int u, int v, int _cost) {
        cost[u][v] = _cost;
        cost[v][u] = -_cost;
    }

    void addEdge(int u, int v, int _capacity, int _cost) {
        addEdge(u, v);
        setCapacity(u, v, _capacity);
        setCost(u, v, _cost);
    }

    pair<int, int> getMinCostMaxFlow() {
        pair<int, int> ret(0, 0);  // (cost, flow)

        vector<int> prev(size);
        vector<bool> inQueue(size);
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
                    ASSERT(capacity[cur][next] - flow[cur][next] >= 0);
                    if (capacity[cur][next] - flow[cur][next] == 0)
                        continue;

                    if (minCost[cur] + cost[cur][next] < minCost[next]) {
                        minCost[next] = minCost[cur] + cost[cur][next];
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
                ret.first += cost[prev[i]][i] * bottleneck;
                flow[prev[i]][i] += bottleneck;
                flow[i][prev[i]] -= bottleneck;
            }

            ret.second += bottleneck;
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int source = 0, sink = n + m + 1;
    // 서점 1 ~ m, 사람 m + 1 ~ m + n
    FlowNetwork network(n + m + 2, source, sink);

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
            network.addEdge(i, j);
            int capacity;
            cin >> capacity;
            network.setCapacity(i, j, capacity);
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + n; j++) {
            int cost;
            cin >> cost;
            network.setCost(i, j, cost);
        }
    }

    pair<int, int> answer = network.getMinCostMaxFlow();
    cout << answer.second << '\n' << answer.first;
}