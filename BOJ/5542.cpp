#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

struct DisjointSet {
    int n;
    vector<int> parent;

    DisjointSet(int _n) : n(_n), parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findParent(int x) {
        if (parent[x] != x)
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u);
        v = findParent(v);

        if (u != v)
            parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

struct Edge {
    int to, cost;
};
vector<Edge> adj[101010];
int minDist[101010];

struct Query {
    int from, to;

    int lo, hi;

    int mid() { return (lo + hi) / 2; }
};
Query queries[101010];

struct QueryComparator {
    bool operator()(int i, int j) {
        const Query &a = queries[i], &b = queries[j];
        return (a.lo + a.hi) / 2 < (b.lo + b.hi) / 2;
    }
};
using QueryQueueType = priority_queue<int, vector<int>, QueryComparator>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K, Q;
    cin >> N >> M >> K >> Q;

    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    fill(minDist, minDist + N + 1, INF);
    MinHeap<pair<int, int>> heapq;

    for (int i = 0; i < K; i++) {
        int v;
        cin >> v;

        minDist[v] = 0;
        heapq.emplace(minDist[v], v);
    }
    while (not heapq.empty()) {
        auto [curDist, cur] = heapq.top();
        heapq.pop();

        if (curDist > minDist[cur])
            continue;

        for (auto [nxt, edgeCost] : adj[cur]) {
            if (curDist + edgeCost < minDist[nxt]) {
                minDist[nxt] = curDist + edgeCost;
                heapq.emplace(minDist[nxt], nxt);
            }
        }
    }

    vector<int> vertices;
    vertices.reserve(N);
    for (int i = 1; i <= N; i++)
        vertices.emplace_back(i);
    sort(vertices.begin(), vertices.end(),
         [&](int a, int b) { return minDist[a] > minDist[b]; });

    int maxDist = minDist[vertices.front()];

    QueryQueueType queryQueue;
    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;

        queries[i] = Query(u, v, 0, maxDist);
        queryQueue.push(i);
    }

    while (not queryQueue.empty()) {
        int curMinDIst = INF;
        DisjointSet disjointSet(N + 1);
        QueryQueueType nextQueryQueue;

        for (int i = 0; i < N; i++) {
            int cur = vertices[i];

            while (not queryQueue.empty() and
                   queries[queryQueue.top()].mid() > minDist[cur]) {
                int queryIndex = queryQueue.top();
                queryQueue.pop();
                Query& q = queries[queryIndex];
                if (disjointSet.isConnected(q.from, q.to))
                    q.lo = q.mid() + 1;
                else
                    q.hi = q.mid();

                if (q.lo < q.hi)
                    nextQueryQueue.push(queryIndex);
            }

            curMinDIst = minDist[cur];

            for (auto [nxt, _] : adj[cur]) {
                if (minDist[nxt] < curMinDIst)
                    continue;

                disjointSet.unionParent(cur, nxt);
            }
        }

        while (not queryQueue.empty()) {
            int queryIndex = queryQueue.top();
            queryQueue.pop();
            Query& q = queries[queryIndex];
            if (disjointSet.isConnected(q.from, q.to))
                q.lo = q.mid() + 1;
            else
                q.hi = q.mid();

            if (q.lo < q.hi)
                nextQueryQueue.push(queryIndex);
        }

        swap(queryQueue, nextQueryQueue);
    }

    for (int i = 0; i < Q; i++)
        println("{}", queries[i].lo - 1);

    return 0;
}