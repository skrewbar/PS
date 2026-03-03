#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr double INF = 1e9, EPS = 1e-9;

struct FlowNetwork {
    size_t size;
    int source, sink;

    struct Edge {
        int to, flow, capacity;
        double cost;

        int rev;
    };
    vector<vector<Edge>> adj;

    FlowNetwork(size_t size, int source, int sink)
        : size(size), source(source), sink(sink), adj(size) {}

    void addEdge(int from, int to, int capacity, double cost) {
        adj[from].emplace_back(to, 0, capacity, cost, adj[to].size());
        adj[to].emplace_back(from, 0, 0, -cost, adj[from].size() - 1);
    }

    double getMinCostOfMaxFlow() {
        double ret = 0;

        vector<int> prevVertex(size);
        vector<int> prevEdge(size);
        vector<double> minCost(size);
        vector<bool> inQueue(size);
        queue<int> q;
        while (true) {
            ranges::fill(prevVertex, -1);
            ranges::fill(prevEdge, -1);
            ranges::fill(minCost, INF);
            ranges::fill(inQueue, false);

            minCost[source] = 0;
            q.push(source);
            while (not q.empty()) {
                int cur = q.front();
                q.pop();
                inQueue[cur] = false;

                for (int i = 0; i < adj[cur].size(); i++) {
                    auto [next, flow, capacity, cost, _] = adj[cur][i];
                    if (capacity - flow == 0)
                        continue;

                    if (EPS + minCost[cur] + cost < minCost[next]) {
                        minCost[next] = minCost[cur] + cost;
                        prevVertex[next] = cur;
                        prevEdge[next] = i;

                        if (not inQueue[next]) {
                            q.push(next);
                            inQueue[next] = true;
                        }
                    }
                }
            }

            if (prevVertex[sink] == -1)
                break;

            // in a bipartite matching problem,
            // every augmenting path has a bottleneck of 1
            for (int v = sink; v != source; v = prevVertex[v]) {
                int u = prevVertex[v];

                Edge& edge = adj[u][prevEdge[v]];
                Edge& rev = adj[v][edge.rev];

                ret += edge.cost;
                edge.flow++;
                rev.flow--;
            }
        }

        return ret;
    }
};

struct Point {
    int x, y;

    double dist(const Point& p) const {
        int dx = x - p.x;
        int dy = y - p.y;

        return sqrt(dx * dx + dy * dy);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points;
    points.reserve(2 * N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
        points.emplace_back(-x, y);
    }

    int source = 2 * N, sink = 2 * N + 1;
    FlowNetwork flowNetwork(2 * N + 2, source, sink);
    for (int i = 0; i < N; i++) {
        flowNetwork.addEdge(source, i << 1, 1, 0);
        flowNetwork.addEdge(i << 1 | 1, sink, 1, 0);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            flowNetwork.addEdge(i << 1, j << 1 | 1, 1,
                                points[i << 1].dist(points[j << 1 | 1]) / 2);
        }
    }

    println("{:.3f}", flowNetwork.getMinCostOfMaxFlow());

    return 0;
}