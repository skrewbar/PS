#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

struct FlowNetwork {
    struct Edge {
        int to;
        int capacity;
        int flow = 0;

        Edge(int to, int cap) : to(to), capacity(cap) {}

        Edge* reverse;

        void pushFlow(int f) {
            flow += f;
            reverse->flow -= f;
        }
    };

    vector<vector<Edge*>> adj;
    vector<int> layer,
        work;  // layered 그래프에서 탐색해야 할 간선 번호
    int source = 0, sink;

    FlowNetwork(int v) : adj(v), layer(v), work(v), sink(v - 1) {}

    void addEdge(int u, int v, int c) {
        Edge* edge = new Edge(v, c);
        Edge* reverse = new Edge(u, 0);

        edge->reverse = reverse;
        reverse->reverse = edge;

        adj[u].push_back(edge);
        adj[v].push_back(reverse);
    }

    // s -> t 도달 가능한지 여부를 리턴
    bool buildLayerGraph() {
        queue<int> q;
        q.push(source);

        ranges::fill(layer, -1);
        layer[source] = 0;

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (Edge* edge : adj[cur]) {
                int next = edge->to;
                if (layer[next] != -1)
                    continue;
                if (edge->capacity - edge->flow > 0) {
                    q.push(next);
                    layer[next] = layer[cur] + 1;
                }
            }
        }

        return layer[sink] != -1;
    }

    int pushFlow(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = work[cur]; i < (int)adj[cur].size();
             i++) {  // 증가 경로가 없는 간선은 탐색에서 제외
            Edge* edge = adj[cur][i];
            int next = edge->to;
            int residualCap = edge->capacity - edge->flow;

            if (layer[next] != layer[cur] + 1)
                continue;
            if (residualCap <= 0)
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

        while (buildLayerGraph()) {
            ranges::fill(work, 0);
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

    int n, k, d;
    cin >> n >> k >> d;

    FlowNetwork network(n + d + 2);
    // source = 0, sink = n + d + 1
    // 나머지 정점 n + d 개

    for (int i = 1; i <= d; i++) {
        int maxDish;
        cin >> maxDish;
        network.addEdge(n + i, network.sink, maxDish);
    }

    for (int i = 1; i <= n; i++) {
        network.addEdge(network.source, i, k);

        int z;
        cin >> z;
        while (z--) {
            int dish;
            cin >> dish;
            network.addEdge(i, n + dish, 1);
        }
    }

    cout << network.getMaxFlow();
}