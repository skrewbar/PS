#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

struct Edge {
    int to, capacity, cost, rev;
};

vector<Edge> adj[40404];
int curEdge[40404], minCost[40404];
bool visited[40404];

int V;
int source, sink;

void addEdge(int from, int to, int capacity, int cost) {
    adj[from].emplace_back(to, capacity, cost, adj[to].size());
    adj[to].emplace_back(from, 0, -cost, adj[from].size() - 1);
}

int pushFlow(int cur, int flow) {
    visited[cur] = true;

    if (cur == sink)
        return flow;

    for (int& i = curEdge[cur]; i < adj[cur].size(); i++) {
        Edge& edge = adj[cur][i];

        if (visited[edge.to] or edge.capacity == 0 or
            minCost[edge.to] != minCost[cur] + edge.cost)
            continue;

        int bottleneck = pushFlow(edge.to, min(flow, edge.capacity));
        if (bottleneck == 0)
            continue;

        edge.capacity -= bottleneck;
        adj[edge.to][edge.rev].capacity += bottleneck;

        return bottleneck;
    }

    return 0;
}

bool updateDAG() {
    int m = INF;

    for (int v = 0; v < V; v++) {
        if (not visited[v])
            continue;

        for (auto& [to, capacity, cost, _] : adj[v]) {
            if (capacity and not visited[to])
                m = min(m, minCost[v] + cost - minCost[to]);
        }
    }

    if (m == INF)
        return false;

    for (int v = 0; v < V; v++) {
        if (not visited[v])
            minCost[v] += m;
    }

    return true;
}

int getMinCostOfMaxFlow() {
    int ret = 0;

    ranges::fill(minCost, INF);
    queue<int> q;
    vector<bool> inQueue(V);

    minCost[source] = 0;
    q.push(source);

    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        inQueue[cur] = false;

        for (auto& [to, capacity, cost, _] : adj[cur]) {
            if (capacity == 0 or minCost[to] <= minCost[cur] + cost)
                continue;

            minCost[to] = minCost[cur] + cost;

            if (inQueue[to])
                continue;

            q.push(to);
            inQueue[to] = true;
        }
    }

    do {
        ranges::fill(visited, false);
        ranges::fill(curEdge, 0);

        while (true) {
            int bottleneck = pushFlow(source, INF);
            if (bottleneck == 0)
                break;
            ret += minCost[sink] * bottleneck;

            ranges::fill(visited, false);
        }
    } while (updateDAG());

    return ret;
}

int price[5][5] = {
    {10, 8, 7, 5, 1}, {8, 6, 4, 3, 1}, {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},  {1, 1, 1, 1, 0},
};

int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};

int topu[222][222];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    source = n * m, sink = n * m + 1;
    V = n * m + 2;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'F')
                topu[i][j] = 4;
            else
                topu[i][j] = s[j] - 'A';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            addEdge(i * m + j, sink, 1, 0);

            if ((i + j) % 2 == 1)
                continue;

            addEdge(source, i * m + j, 1, 0);

            for (int k = 0; k < 4; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];

                if (ni < 0 or ni >= n or nj < 0 or nj >= m)
                    continue;

                addEdge(i * m + j, ni * m + nj, 1,
                        -price[topu[i][j]][topu[ni][nj]]);
            }
        }
    }

    println("{}", -getMinCostOfMaxFlow());

    return 0;
}