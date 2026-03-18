#include <queue>
#include <vector>
using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    struct Edge {
        int to, capacity, flow, cost, rev;
    };

    int n, source, sink;
    vector<vector<Edge>> adj;

    FlowNetwork(int _n, int _source, int _sink)
        : n(_n), source(_source), sink(_sink), adj(n) {}

    void addEdge(int from, int to, int capacity, int cost) {
        adj[from].emplace_back(to, capacity, 0, cost, adj[to].size());
        adj[to].emplace_back(from, 0, 0, -cost, adj[from].size() - 1);
    }

    pair<int, int> getMinCostMaxFlow() {
        int mc = 0, mf = 0;

        vector<int> prv(n), prvEdge(n), minCost(n);
        vector<bool> inQueue(n);
        queue<int> q;

        while (true) {
            ranges::fill(prv, -1);
            ranges::fill(minCost, INF);

            minCost[source] = 0;
            q.push(source);

            while (not q.empty()) {
                int cur = q.front();
                q.pop();
                inQueue[cur] = false;

                for (int i = 0; i < adj[cur].size(); i++) {
                    const auto& [to, capacity, flow, cost, _] = adj[cur][i];

                    if (capacity - flow == 0)
                        continue;
                    if (minCost[cur] + cost >= minCost[to])
                        continue;

                    minCost[to] = minCost[cur] + cost;
                    prv[to] = cur;
                    prvEdge[to] = i;

                    if (inQueue[to])
                        continue;

                    q.push(to);
                    inQueue[to] = true;
                }
            }

            if (prv[sink] == -1)
                break;

            int bottleneck = INF;
            for (int i = sink; i != source; i = prv[i]) {
                Edge& edge = adj[prv[i]][prvEdge[i]];

                bottleneck = min(bottleneck, edge.capacity - edge.flow);
            }

            for (int i = sink; i != source; i = prv[i]) {
                Edge& edge = adj[prv[i]][prvEdge[i]];
                Edge& rev = adj[i][edge.rev];

                mc += bottleneck * edge.cost;
                edge.flow += bottleneck;
                rev.flow -= bottleneck;
            }
            mf += bottleneck;
        }

        return {mc, mf};
    }
};