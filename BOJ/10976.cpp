#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    struct Edge {
        int to, capacity, flow;
        Edge* rev;

        Edge(int to, int capacity) : to(to), capacity(capacity), flow(0) {}

        void pushFlow(int f) {
            flow += f;
            rev->flow -= f;
        }

        int residualCapacity() { return capacity - flow; }
    };

    size_t size;
    int source, sink;
    vector<vector<Edge*>> adj;
    vector<int> level, curEdge;

    FlowNetwork(size_t size, int source, int sink)
        : size(size),
          source(source),
          sink(sink),
          adj(size),
          level(size),
          curEdge(size) {}

    ~FlowNetwork() {
        for (auto& edges : adj)
            for (Edge* edge : edges)
                delete edge;
    }

    void addEdge(int from, int to, int capacity) {
        Edge* edge = new Edge(to, capacity);
        Edge* rev = new Edge(from, 0);

        edge->rev = rev;
        rev->rev = edge;

        adj[from].push_back(edge);
        adj[to].push_back(rev);
    }

    bool buildLevelGraph() {
        ranges::fill(level, -1);
        level[source] = 0;

        queue<int> q;
        q.push(source);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (Edge* edge : adj[cur]) {
                if (level[edge->to] != -1 or edge->residualCapacity() == 0)
                    continue;

                level[edge->to] = level[cur] + 1;
                q.push(edge->to);
            }
        }

        return level[sink] != -1;
    }

    int pushFlow(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < (int)adj[cur].size(); i++) {
            Edge* edge = adj[cur][i];

            if (level[cur] + 1 != level[edge->to] or
                edge->residualCapacity() == 0)
                continue;

            int bottleneck =
                pushFlow(edge->to, min(flow, edge->residualCapacity()));
            if (bottleneck) {
                edge->pushFlow(bottleneck);
                return bottleneck;
            }
        }

        return 0;
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

void solve() {
    int n, m;
    cin >> n >> m;

    FlowNetwork network(n + 1, 1, n);

    while (m--) {
        int x, y;
        cin >> x >> y;

        network.addEdge(x, y, (x == 1 or y == n ? 1 : INF));
    }

    print("{}\n", network.getMaxFlow());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}