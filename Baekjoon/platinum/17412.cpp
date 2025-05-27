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

        Edge(int _to, int _capacity) : to(_to), capacity(_capacity) {}

        void pushFlow(int f) {
            flow += f;
            reverse->flow -= f;
        }
    };

    int source, sink;
    vector<vector<Edge*>> adj;
    vector<int> layerNum;
    vector<int> curEdge;

    FlowNetwork(size_t size, int source, int sink)
        : source(source),
          sink(sink),
          adj(size),
          layerNum(size),
          curEdge(size) {}

    void addEdge(int u, int v, int capacity) {
        Edge* edge = new Edge(v, capacity);
        Edge* reverse = new Edge(u, 0);

        edge->reverse = reverse;
        reverse->reverse = edge;

        adj[u].push_back(edge);
        adj[v].push_back(reverse);
    }

    bool buildLayeredNetwork() {
        ranges::fill(layerNum, -1);
        layerNum[source] = 0;

        queue<int> q;
        q.push(source);
        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (Edge* edge : adj[cur]) {
                auto [next, capacity, flow, _] = *edge;

                if (layerNum[next] != -1 or capacity - flow <= 0)
                    continue;
                layerNum[next] = layerNum[cur] + 1;
                q.push(next);
            }
        }
        return layerNum[sink] != -1;
    }

    int pushFlow(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < (int)adj[cur].size(); i++) {
            Edge* edge = adj[cur][i];
            auto [next, edgeCap, edgeFlow, _] = *edge;
            int residualCap = edgeCap - edgeFlow;
            if (layerNum[next] != layerNum[cur] + 1 or residualCap <= 0)
                continue;

            int f = pushFlow(next, min(flow, residualCap));
            if (f > 0) {
                edge->pushFlow(f);
                return f;
            }
        }
        return 0;
    }

    int getMaxFlow() {
        int maxFlow = 0;

        while (buildLayeredNetwork()) {
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

    int n, p;
    cin >> n >> p;

    FlowNetwork network(n, 0, 1);
    for (int i = 0; i < p; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        network.addEdge(u, v, 1);
    }

    cout << network.getMaxFlow();
}