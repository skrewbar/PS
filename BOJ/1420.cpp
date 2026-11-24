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

    vector<vector<Edge*>> adj;
    vector<int> layer;
    vector<int> curEdge;
    int source, sink;

    FlowNetwork(size_t n, int source, int sink)
        : adj(n), layer(n), curEdge(n), source(source), sink(sink) {}

    void addEdge(int u, int v, int capacity) {
        Edge* edge = new Edge(v, capacity);
        Edge* rev = new Edge(u, 0);

        edge->reverse = rev;
        rev->reverse = edge;

        adj[u].push_back(edge);
        adj[v].push_back(rev);
    }

    bool buildLayeredGraph() {
        ranges::fill(layer, -1);
        layer[source] = 0;

        queue<int> q;
        q.push(source);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            for (Edge* edge : adj[cur]) {
                int next = edge->to;
                if (layer[next] != -1 or edge->residualCapacity() == 0)
                    continue;
                layer[next] = layer[cur] + 1;
                q.push(next);
            }
        }

        return layer[sink] != -1;
    }

    int pushFlow(int cur, int flow) {
        if (cur == sink)
            return flow;

        for (int& i = curEdge[cur]; i < (int)adj[cur].size(); i++) {
            Edge* edge = adj[cur][i];
            int next = edge->to;

            if (layer[next] != layer[cur] + 1 or edge->residualCapacity() == 0)
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

        while (buildLayeredGraph()) {
            ranges::fill(curEdge, 0);

            int f;
            while ((f = pushFlow(source, INF)) > 0)
                maxFlow += f;
        }

        return maxFlow;
    }
};

int n, m;
vector<vector<bool>> isWall;
struct Grid {
    int i, j, in, out;

    Grid() = default;

    Grid(int i, int j) : i(i), j(j) {
        int num = i * m + j;
        in = num << 1;
        out = num << 1 | 1;
    }

    bool isValid() {
        return 0 <= i and i < n and 0 <= j and j < m and not isWall[i][j];
    }

    bool operator==(const Grid& grid) const = default;

    int manhattanDist(const Grid& grid) const {
        return abs(i - grid.i) + abs(j - grid.j);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    Grid dohyun, school;

    // 정점 (i, j)의 번호는 i*m + j
    isWall = vector(n, vector(m, false));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'K')
                dohyun = Grid(i, j);
            else if (s[j] == 'H')
                school = Grid(i, j);
            else if (s[j] == '#')
                isWall[i][j] = true;
        }
    }

    if (dohyun.manhattanDist(school) == 1) {
        cout << -1;
        return 0;
    }

    FlowNetwork network(n * m << 1, dohyun.out, school.in);

    array<int, 4> di = {1, -1, 0, 0};
    array<int, 4> dj = {0, 0, 1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Grid grid(i, j);
            if (not grid.isValid())
                continue;
            network.addEdge(grid.in, grid.out, 1);

            for (int k = 0; k < (int)di.size(); k++) {
                Grid neighborGrid(i + di[k], j + dj[k]);
                if (not neighborGrid.isValid())
                    continue;
                network.addEdge(grid.out, neighborGrid.in, 1);
            }
        }
    }

    cout << network.getMaxFlow();
    return 0;
}