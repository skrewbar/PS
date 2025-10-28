#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct DisjointSet {
    vector<int> parent;

    DisjointSet(size_t size) : parent(size) {
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int findParent(int v) {
        if (parent[v] != v)
            parent[v] = findParent(parent[v]);
        return parent[v];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);

        if (u != v)
            parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

int N, M;

vector<pair<int, int>> adj[1010];
int maxBetween[1010][1010];

void findMaxFrom(int start) {
    queue<int> q;
    q.push(start);

    vector<bool> visited(N + 1);
    visited[start] = true;

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (auto [nxt, cost] : adj[now]) {
            if (visited[nxt])
                continue;
            visited[nxt] = true;
            maxBetween[start][nxt] =
                max({maxBetween[start][nxt], maxBetween[start][now], cost});

            q.push(nxt);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    vector<tuple<int, int, int>> edges(M);

    for (int i = 0; i < M; i++) {
        int A, B, C;
        cin >> A >> B >> C;

        edges.emplace_back(A, B, C);
    }

    sort(edges.begin(), edges.end(),
         [](auto a, auto b) { return get<2>(a) < get<2>(b); });

    DisjointSet disjointSet(N + 1);
    int sum = 0;
    for (auto& [A, B, C] : edges) {
        if (disjointSet.isConnected(A, B))
            continue;

        disjointSet.unionParent(A, B);
        adj[A].emplace_back(B, C);
        adj[B].emplace_back(A, C);
        sum += C;
    }

    for (int i = 1; i <= N; i++)
        findMaxFrom(i);

    int Q;
    cin >> Q;
    while (Q--) {
        int X, Y;
        cin >> X >> Y;

        println("{}", sum - maxBetween[X][Y]);
    }

    return 0;
}