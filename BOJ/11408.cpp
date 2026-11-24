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
          flow(size, vector<int>(size)),
          source(source),
          sink(sink),
          size(size) {}

    void addEdge(int u, int v, int _capacity, int _cost) {
        adj[u].push_back(v);
        adj[v].push_back(u);

        capacity[u][v] = _capacity;
        capacity[v][u] = 0;

        cost[u][v] = _cost;
        cost[v][u] = -_cost;
    }

    struct MinCostMaxFlow {
        int minCost, maxFlow;
    };
    MinCostMaxFlow getMinCostMaxFlow() {
        MinCostMaxFlow ret(0, 0);

        vector<int> prev(size);
        vector<int> minCost(size);
        vector<bool> inQueue(size);

        while (true) {
            ranges::fill(prev, -1);
            ranges::fill(minCost, INF);
            minCost[source] = 0;
            ranges::fill(inQueue, false);
            inQueue[source] = true;

            queue<int> q;
            q.push(source);
            while (not q.empty()) {
                int cur = q.front();
                q.pop();
                inQueue[cur] = false;

                for (int next : adj[cur]) {
                    if (capacity[cur][next] - flow[cur][next] == 0)
                        continue;

                    if (minCost[cur] + cost[cur][next] < minCost[next]) {
                        minCost[next] = minCost[cur] + cost[cur][next];
                        prev[next] = cur;
                        if (not inQueue[next]) {
                            q.push(next);
                            inQueue[next] = true;
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
                ret.minCost += cost[prev[i]][i] * bottleneck;
                flow[prev[i]][i] += bottleneck;
                flow[i][prev[i]] -= bottleneck;
            }
            ret.maxFlow += bottleneck;
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
    FlowNetwork network(n + m + 2, source, sink);

    // 일 1 ~ m, 사람 m + 1 ~ m + n
    for (int i = 1; i <= m; i++)
        network.addEdge(i, sink, 1, 0);
    for (int i = m + 1; i <= m + n; i++)
        network.addEdge(source, i, 1, 0);

    for (int i = m + 1; i <= m + n; i++) {
        int count;
        cin >> count;
        while (count--) {
            int work, salary;
            cin >> work >> salary;
            network.addEdge(i, work, 1, salary);
        }
    }

    auto [minCost, maxFlow] = network.getMinCostMaxFlow();
    cout << maxFlow << '\n' << minCost;
}