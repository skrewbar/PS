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
        int to, capacity, flow = 0;
        Edge* reverse;

        Edge(int to, int capacity) : to(to), capacity(capacity) {}

        void pushFlow(int f) {
            flow += f;
            reverse->flow -= f;
        }

        int residualCapacity() { return capacity - flow; }
    };

    int source, sink;
    vector<vector<Edge*>> adj;
    vector<int> level;
    vector<int> curEdge;

    FlowNetwork(size_t size, int source, int sink)
        : source(source), sink(sink), adj(size), level(size), curEdge(size) {}

    void addEdge(int u, int v, int capacity) {
        Edge* edge = new Edge(v, capacity);
        Edge* rev = new Edge(u, 0);

        edge->reverse = rev;
        rev->reverse = edge;

        adj[u].push_back(edge);
        adj[v].push_back(rev);
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
                if (level[edge->to] != -1 or edge->residualCapacity() <= 0)
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
            if (level[edge->to] != level[cur] + 1 or
                edge->residualCapacity() <= 0)
                continue;

            int f = pushFlow(edge->to, min(flow, edge->residualCapacity()));
            if (f > 0) {
                edge->pushFlow(f);
                return f;
            }
        }
        return 0;
    }

    int getMaxFlow() {
        int maxFlow = 0;

        while (buildLevelGraph()) {
            ranges::fill(curEdge, 0);
            int f;
            while ((f = pushFlow(source, INF)) > 0)
                maxFlow += f;
        }
        return maxFlow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // in정점: i << 1
    // out정점: i << 1 | 1
    int source = 1 << 1 | 1, sink = n << 1;
    FlowNetwork network((n + 1) << 1, source, sink);

    for (int i = 1; i <= n; i++) {
        int ai;
        cin >> ai;
        if (ai == -1)
            continue;

        network.addEdge(i << 1, i << 1 | 1, ai);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        network.addEdge(u << 1 | 1, v << 1, INF);
        network.addEdge(v << 1 | 1, u << 1, INF);
    }

    int minCut = network.getMaxFlow();
    cout << (minCut <= k ? "YES" : "NO");

    return 0;
}