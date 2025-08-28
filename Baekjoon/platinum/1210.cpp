#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = INT_MAX;

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

            int f = pushFlow(edge->to, min(flow, edge->residualCapacity()));
            if (f) {
                edge->pushFlow(f);
                return f;
            }
        }

        return 0;
    }

    vector<int> getAnswer() {
        while (buildLevelGraph()) {
            ranges::fill(curEdge, 0);
            pushFlow(source, INF);
        }

        vector<int> answer;
        vector<bool> visited(size);

        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (Edge* edge : adj[cur]) {
                if (visited[edge->to] or edge->residualCapacity() == 0)
                    continue;
                visited[edge->to] = true;

                q.push(edge->to);
            }
        }

        for (int i = 1; i <= (int)(size >> 1); i++) {
            if (visited[i << 1] and not visited[i << 1 | 1])
                answer.push_back(i);
        }

        return answer;
    }
};

int in(int number) {
    return number << 1;
}
int out(int number) {
    return number << 1 | 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int source, sink;
    cin >> source >> sink;

    FlowNetwork network((n + 1) << 1, in(source), out(sink));

    for (int i = 1; i <= n; i++) {
        int cost;
        cin >> cost;

        network.addEdge(in(i), out(i), cost);
    }

    while (m--) {
        int u, v;
        cin >> u >> v;

        network.addEdge(out(u), in(v), INF);
        network.addEdge(out(v), in(u), INF);
    }

    vector<int> ans = network.getAnswer();
    sort(ans.begin(), ans.end());
    for (auto i : ans)
        cout << i << ' ';

    return 0;
}