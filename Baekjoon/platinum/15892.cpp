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

        int residualCapacity() { return capacity - flow; }

        void pushFlow(int f) {
            flow += f;
            rev->flow -= f;
        }
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

    void addUndirectedEdge(int from, int to, int capacity) {
        Edge *edge = new Edge(to, capacity), *rev = new Edge(from, capacity);
        edge->rev = rev, rev->rev = edge;

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
                int next = edge->to;
                if (level[next] != -1 or edge->residualCapacity() == 0)
                    continue;
                level[next] = level[now] + 1;
                q.push(next);
            }
        }
        return level[sink] != -1;
    }

    int pushFlow(int now, int flow) {
        if (now == sink)
            return flow;

        for (int& i = curEdge[now]; i < (int)adj[now].size(); i++) {
            Edge* edge = adj[now][i];
            int next = edge->to;
            if (level[next] != level[now] + 1 or edge->residualCapacity() == 0)
                continue;

            int f = pushFlow(next, min(flow, edge->residualCapacity()));
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

    int n, m;
    cin >> n >> m;

    FlowNetwork network(n + 1, 1, n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        network.addUndirectedEdge(a, b, c);
    }

    print("{}", network.getMaxFlow());
    return 0;
}