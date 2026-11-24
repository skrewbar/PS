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

        int residualCapacity() { return capacity - flow; }

        void pushFlow(int f) {
            flow += f;
            reverse->flow -= f;
        }
    };

    int source, sink;
    vector<vector<Edge*>> adj;
    vector<int> level;
    vector<int> curEdge;
    FlowNetwork(size_t size, int source, int sink)
        : source(source), sink(sink), adj(size), level(size), curEdge(size) {
        ASSERT(source >= 0);
        ASSERT(sink < size);
    }

    void addEdge(int u, int v, int c) {
        Edge* edge = new Edge(v, c);
        Edge* reverse = new Edge(u, 0);

        edge->reverse = reverse;
        reverse->reverse = edge;

        adj[u].push_back(edge);
        adj[v].push_back(reverse);
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
                int next = edge->to;
                if (level[next] != -1 or edge->residualCapacity() <= 0)
                    continue;
                level[next] = level[cur] + 1;
                q.push(next);
            }
        }
        return level[sink] != -1;
    }

    int pushFlow(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < (int)adj[cur].size(); i++) {
            Edge* edge = adj[cur][i];
            int next = edge->to;
            if (level[next] != level[cur] + 1 or edge->residualCapacity() <= 0)
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

    int source = 0, sink = n + m + 1;
    FlowNetwork network(n + m + 2, source, sink);
    for (int i = m + 1; i <= m + n; i++) {
        int buy;
        cin >> buy;
        network.addEdge(i, sink, buy);
    }
    for (int i = 1; i <= m; i++) {
        int stock;
        cin >> stock;
        network.addEdge(source, i, stock);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + n; j++) {
            int sellableCnt;
            cin >> sellableCnt;
            network.addEdge(i, j, sellableCnt);
        }
    }

    cout << network.getMaxFlow();
}