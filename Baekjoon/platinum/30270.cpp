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
        Edge* rev;

        Edge(int to, int capacity) : to(to), capacity(capacity) {}

        void pushFlow(int f) {
            flow += f;
            rev->flow -= f;
        }

        int residualCapacity() { return capacity - flow; }
    };

    int source, sink;
    vector<int> level, curEdge;
    vector<vector<Edge*>> adj;

    FlowNetwork(size_t size, int source, int sink)
        : source(source), sink(sink), level(size), curEdge(size), adj(size) {}

    void addEdge(int from, int to, int capacity) {
        Edge* edge = new Edge(to, capacity);
        Edge* rev = new Edge(from, capacity);

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

            if (level[edge->to] != level[now] + 1 or
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

void solve(int tc) {
    int n, c;
    cin >> n >> c;

    int source = 0, sink = n + 1;
    FlowNetwork network(n + 2, source, sink);

    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;

        if (t == 1)
            network.addEdge(source, i, INF);
        else if (t == 2)
            network.addEdge(i, sink, INF);
    }

    while (c--) {
        int s, t;
        cin >> s >> t;
        network.addEdge(s, t, 1);
    }

    print("Data Set {}:\n{}\n\n", tc, network.getMaxFlow());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    for (int i = 1; i <= K; i++)
        solve(i);

    return 0;
}