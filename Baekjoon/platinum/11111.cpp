#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    vector<vector<int>> adj, flow, capacity, cost;
    size_t size;
    int source, sink;
    FlowNetwork(size_t size, int source, int sink)
        : adj(size),
          flow(size, vector<int>(size)),
          capacity(size, vector<int>(size)),
          cost(size, vector<int>(size)),
          size(size),
          source(source),
          sink(sink) {}

    void addEdge(int u, int v, int _capacity, int _cost) {
        adj[u].push_back(v);
        adj[v].push_back(u);

        capacity[u][v] = _capacity;
        capacity[v][u] = 0;

        cost[u][v] = _cost;
        cost[v][u] = -_cost;
    }

    int getMinCostOfMaxFlow() {
        int ret = 0;

        vector<int> prev(size), minCost(size);
        vector<bool> inQueue(size);
        queue<int> q;
        while (true) {
            ranges::fill(prev, -1);
            ranges::fill(minCost, INF);
            ranges::fill(inQueue, false);

            minCost[source] = 0;
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
                ret += cost[prev[i]][i] * bottleneck;
                flow[prev[i]][i] += bottleneck;
                flow[i][prev[i]] -= bottleneck;
            }
        }

        return ret;
    }
};

int price[5][5] = {
    {10, 8, 7, 5, 1}, {8, 6, 4, 3, 1}, {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},  {1, 1, 1, 1, 0},
};

int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int source = n * m, sink = n * m + 1;

    FlowNetwork network(n * m + 2, source, sink);

    vector<vector<int>> topu(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'F')
                topu[i][j] = 4;
            else
                topu[i][j] = s[j] - 'A';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            network.addEdge(i * m + j, sink, 1, 0);

            if ((i + j) & 1)
                continue;

            network.addEdge(source, i * m + j, 1, 0);

            for (int k = 0; k < 4; k++) {
                int ni = i + di[k], nj = j + dj[k];

                if (ni < 0 or ni >= n or nj < 0 or nj >= m)
                    continue;

                network.addEdge(i * m + j, ni * m + nj, 1,
                                -price[topu[i][j]][topu[ni][nj]]);
            }
        }
    }

    cout << -network.getMinCostOfMaxFlow();
}