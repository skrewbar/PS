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
        int to, residualCapacity, cost, rev;
    };

    int n, source, sink;
    vector<vector<Edge>> adj;

    FlowNetwork(int _n, int _source, int _sink)
        : n(_n), source(_source), sink(_sink), adj(n) {}

    void addEdge(int from, int to, int capacity, int cost) {
        adj[from].emplace_back(to, capacity, cost, adj[to].size());
        adj[to].emplace_back(from, 0, -cost, adj[from].size() - 1);
    }

    int getMinCostMaxFlow() {
        int ret = 0;

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
                    auto [to, residualCapacity, cost, _] = adj[cur][i];

                    if (residualCapacity == 0)
                        continue;

                    if (minCost[cur] + cost < minCost[to]) {
                        minCost[to] = minCost[cur] + cost;
                        prv[to] = cur;
                        prvEdge[to] = i;

                        if (not inQueue[to]) {
                            q.push(to);
                            inQueue[to] = true;
                        }
                    }
                }
            }

            if (prv[sink] == -1)
                break;

            int bottleneck = INF;
            for (int i = sink; i != source; i = prv[i])
                bottleneck =
                    min(bottleneck, adj[prv[i]][prvEdge[i]].residualCapacity);

            for (int i = sink; i != source; i = prv[i]) {
                auto& edge = adj[prv[i]][prvEdge[i]];
                auto& rev = adj[i][edge.rev];

                ret += edge.cost * bottleneck;
                edge.residualCapacity -= bottleneck;
                rev.residualCapacity += bottleneck;
            }
        }

        return ret;
    }
};

struct Player {
    int A, H, L;
} players[333];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> players[i].A;
    for (int i = 1; i <= N; i++)
        cin >> players[i].H;
    for (int i = 1; i <= N; i++)
        cin >> players[i].L;

    sort(players + 1, players + N + 1,
         [&](const Player& a, const Player& b) { return a.A < b.A; });

    int source = 0, sink = 2*N + 1;
    FlowNetwork flowNetwork(2*N + 2, source, sink);

    for (int i = 1; i <= N; i++)
        flowNetwork.addEdge(source, i, players[i].L - (i < N), players[i].H);
    for (int i = N; i >= 1; i--) {
        for (int j = i - 1; j >= 1; j--)
            flowNetwork.addEdge(i, N + j, 1, -(players[i].A ^ players[j].A));
    }
    for (int i = 1; i < N; i++)
        flowNetwork.addEdge(N + i, sink, 1, players[i].H);

    println("{}", -flowNetwork.getMinCostMaxFlow());

    return 0;
}