#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int square(int x) {
    return x * x;
}

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
        int mc = 0;
        int mf = 0;

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
                    auto [to, capacity, flow, cost, _] = adj[cur][i];

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

int inTime[55], outTime[55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> inTime[i];
    for (int i = 1; i <= N; i++)
        cin >> outTime[i];

    int T;
    cin >> T;
    int F;
    cin >> F;

    int source = 0, sink = 2 * N + 1;
    FlowNetwork flowNetwork(2 * N + 2, source, sink);

    for (int i = 1; i <= N; i++)
        flowNetwork.addEdge(source, i, 1, 0);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (inTime[i] >= outTime[j])
                continue;

            int cost = min(square(T - (outTime[j] - inTime[i])), F);

            flowNetwork.addEdge(i, N + j, 1,
                                (outTime[j] - inTime[i] < T ? cost : 0));
        }
    }

    for (int j = N + 1; j <= N + N; j++)
        flowNetwork.addEdge(j, sink, 1, 0);

    auto [minAnswer, maxFlow] = flowNetwork.getMinCostMaxFlow();
    if (maxFlow < N) {
        println("-1");
        return 0;
    }

    for (auto& v : flowNetwork.adj) {
        for (auto& edge : v) {
            edge.cost = -edge.cost;
            edge.flow = 0;
        }
    }

    auto [maxAnswer, _] = flowNetwork.getMinCostMaxFlow();
    maxAnswer = -maxAnswer;

    println("{} {}", minAnswer, maxAnswer);

    return 0;
}