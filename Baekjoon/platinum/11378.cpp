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
        Edge* rev;
        int to, capacity, flow = 0;

        Edge(int to, int capacity) : to(to), capacity(capacity) {}

        void pushFlow(int f) {
            flow += f;
            rev->flow -= f;
        }
        int residualCapacity() { return capacity - flow; }
    };

    size_t size;
    int source, sink;

    vector<vector<Edge*>> adj;
    vector<int> curEdge, level;

    FlowNetwork(size_t size, int source, int sink)
        : size(size),
          source(source),
          sink(sink),
          adj(size),
          curEdge(size),
          level(size) {}

    void addEdge(int from, int to, int capacity) {
        Edge *edge = new Edge(to, capacity), *rev = new Edge(from, 0);
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
            int now = q.front();
            q.pop();

            for (Edge* edge : adj[now]) {
                if (level[edge->to] != -1 or edge->residualCapacity() == 0)
                    continue;
                level[edge->to] = level[now] + 1;
                q.push(edge->to);
            }
        }

        return level[sink] != -1;
    }

    int pushFlow(int now, int flow) {
        if (now == sink)
            return flow;

        for (int& i = curEdge[now]; i < (int)adj[now].size(); i++) {
            Edge* edge = adj[now][i];

            if (level[now] + 1 != level[edge->to] or
                edge->residualCapacity() == 0)
                continue;

            int f = pushFlow(edge->to, min(flow, edge->residualCapacity()));
            if (f) {
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
            while ((f = pushFlow(source, INF)))
                maxFlow += f;
        }

        return maxFlow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    int source = N + M + 1, bridge = N + M + 2, sink = N + M + 3;
    FlowNetwork network(N + M + 4, source, sink);
    network.addEdge(source, bridge, K);
    for (int i = 1; i <= N; i++) {
        network.addEdge(source, i, 1);
        network.addEdge(bridge, i, K);
    }
    for (int i = N + 1; i <= N + M; i++)
        network.addEdge(i, sink, 1);

    for (int i = 1; i <= N; i++) {
        int cnt;
        cin >> cnt;
        while (cnt--) {
            int work;
            cin >> work;
            network.addEdge(i, N + work, 1);
        }
    }

    cout << network.getMaxFlow();
    return 0;
}