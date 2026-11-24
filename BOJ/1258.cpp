#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    struct Edge {
        int to, capacity, flow, cost, rev;
    };

    int n, source, sink;
    vector<vector<Edge>> adj;
    vector<int> curEdge, h;
    vector<bool> visited;

    FlowNetwork(int n, int source, int sink)
        : n(n),
          source(source),
          sink(sink),
          adj(n),
          curEdge(n),
          h(n),
          visited(n) {}

    void addEdge(int from, int to, int capacity, int cost) {
        adj[from].emplace_back(to, capacity, 0, cost, adj[to].size());
        adj[to].emplace_back(from, 0, 0, -cost, adj[from].size() - 1);
    }

    int pushFlow(int cur, int flow) {
        visited[cur] = true;

        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < adj[cur].size(); i++) {
            Edge& edge = adj[cur][i];

            if (visited[edge.to] or edge.capacity - edge.flow == 0 or
                h[cur] + edge.cost - h[edge.to] != 0)
                continue;

            int bottleneck =
                pushFlow(edge.to, min(flow, edge.capacity - edge.flow));

            if (bottleneck == 0)
                continue;

            edge.flow += bottleneck;
            adj[edge.to][edge.rev].flow -= bottleneck;

            return bottleneck;
        }

        return 0;
    }

    bool updateDAG() {
        int delta = INF;

        for (int i = 0; i < n; i++) {
            if (not visited[i])
                continue;

            for (auto& [to, capacity, flow, cost, _] : adj[i]) {
                if (capacity - flow != 0 and not visited[to])
                    delta = min(delta, h[i] + cost - h[to]);
            }
        }

        if (delta == INF)
            return false;

        for (int i = 0; i < n; i++) {
            if (not visited[i])
                h[i] += delta;
        }

        return true;
    }

    int getMinCostOfMaxFlow() {
        int mc = 0;

        ranges::fill(h, INF);
        queue<int> q;
        vector<bool> inQueue(n);

        h[source] = 0;
        q.push(source);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();
            inQueue[cur] = false;

            for (auto& [to, capacity, flow, cost, _] : adj[cur]) {
                if (capacity - flow == 0 or h[to] <= h[cur] + cost)
                    continue;

                h[to] = h[cur] + cost;

                if (inQueue[to])
                    continue;

                q.push(to);
                inQueue[to] = true;
            }
        }

        do {
            ranges::fill(curEdge, 0);
            ranges::fill(visited, false);

            while (true) {
                int bottleneck = pushFlow(source, INF);
                if (bottleneck == 0)
                    break;
                mc += bottleneck * h[sink];

                ranges::fill(visited, false);
            }

        } while (updateDAG());

        return mc;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int source = 0, sink = N * 2 + 1;
    FlowNetwork flowNetwork(N * 2 + 2, source, sink);

    for (int i = 1; i <= N; i++) {
        flowNetwork.addEdge(source, i, 1, 0);
        flowNetwork.addEdge(N + i, sink, 1, 0);

        for (int j = N + 1; j <= 2 * N; j++) {
            int t;
            cin >> t;

            flowNetwork.addEdge(i, j, 1, t);
        }
    }

    cout << flowNetwork.getMinCostOfMaxFlow();

    return 0;
}