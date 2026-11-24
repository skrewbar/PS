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

        void push(int f) {
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

    int push(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < (int)adj[cur].size(); i++) {
            Edge* edge = adj[cur][i];

            if (level[edge->to] != level[cur] + 1 or
                edge->residualCapacity() == 0)
                continue;

            int f = push(edge->to, min(flow, edge->residualCapacity()));
            if (f) {
                edge->push(f);
                return f;
            }
        }

        return 0;
    }

    int getMinCut() {
        int maxFlow = 0;

        while (buildLevelGraph()) {
            ranges::fill(curEdge, 0);

            int f;
            while ((f = push(source, INF)))
                maxFlow += f;
        }

        return maxFlow;
    }

    set<int> getSourceSideVertices() {
        set<int> ret;

        vector<bool> visited(size);
        visited[source] = true;

        queue<int> q;
        q.push(source);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (Edge* edge : adj[cur]) {
                if (visited[edge->to] or edge->residualCapacity() == 0)
                    continue;

                visited[edge->to] = true;
                ret.insert(edge->to);
                q.push(edge->to);
            }
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int source = 0, sink = N + 1;
    FlowNetwork network(N + 2, source, sink);

    for (int i = 1; i <= N; i++) {
        int faction;
        cin >> faction;

        if (faction == 1)
            network.addEdge(source, i, INF);
        else if (faction == 2)
            network.addEdge(i, sink, INF);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int w;
            cin >> w;

            if (j <= i)
                continue;

            if (w)
                network.addEdge(i, j, w);
        }
    }

    cout << network.getMinCut() << '\n';

    set<int> progressive = network.getSourceSideVertices();
    for (int i : progressive)
        cout << i << ' ';
    cout << '\n';
    for (int i = 1; i <= N; i++)
        if (not progressive.contains(i))
            cout << i << ' ';
    cout << '\n';

    return 0;
}