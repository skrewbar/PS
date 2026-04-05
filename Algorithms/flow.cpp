#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    struct Edge {
        int to, capacity, flow, rev;
    };

    int source, sink;
    vector<vector<Edge>> adj;
    vector<int> level, curEdge;

    FlowNetwork(int n, int _source, int _sink)
        : source(_source), sink(_sink), adj(n), level(n), curEdge(n) {}

    void addEdge(int from, int to, int capacity) {
        adj[from].emplace_back(to, capacity, 0, adj[to].size());
        adj[to].emplace_back(from, 0, 0, adj[from].size() - 1);
    }

    int pushFlow(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < adj[cur].size(); i++) {
            auto& [to, capacity, edgeFlow, rev] = adj[cur][i];

            if (level[to] != level[cur] + 1 or capacity - edgeFlow == 0)
                continue;

            int bottleneck = pushFlow(to, min(flow, capacity - edgeFlow));
            if (bottleneck) {
                edgeFlow += bottleneck;
                adj[to][rev].flow -= bottleneck;

                return bottleneck;
            }
        }

        return 0;
    }

    bool buildLevelGraph() {
        ranges::fill(level, -1);

        queue<int> q;

        level[source] = 0;
        q.push(source);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (const auto& [to, capacity, flow, _] : adj[cur]) {
                if (level[to] != -1 or capacity - flow == 0)
                    continue;

                level[to] = level[cur] + 1;
                q.push(to);
            }
        }

        return level[sink] != -1;
    }

    int getMaxFlow() {
        int maxFlow = 0;

        while (buildLevelGraph()) {
            ranges::fill(curEdge, 0);
            int f;
            while ((f = pushFlow(source, INF)))
                maxFlow += f;
        }

        return maxFlow;
    }
};