#include <bits/stdc++.h>
using namespace std;

#define by(x) [&](const auto& a, const auto& b) { return a.x < b.x; }
#define by_desc(x) [&](const auto& a, const auto& b) { return a.x > b.x; }

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findParent(int x) {
        if (x != parent[x])
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);

        if (u != v)
            parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

int parent[101010], rounds[101010];
bool seperated[101010];

struct Query {
    int idx, A, B, C;
} queries[101010];
bool ans[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        cin >> parent[i];
        if (parent[i] == -1)
            parent[i] = i;
    }

    for (int i = 1; i <= M; i++) {
        int x;
        cin >> x;

        if (seperated[x])
            continue;
        seperated[x] = true;
        rounds[i] = x;
    }

    DisjointSet disjointSet(N + 1);

    for (int i = 1; i <= N; i++) {
        if (not seperated[i])
            disjointSet.unionParent(i, parent[i]);
    }

    for (int i = 1; i <= K; i++) {
        Query& q = queries[i];
        q.idx = i;
        cin >> q.A >> q.B >> q.C;
    }
    sort(queries + 1, queries + K + 1, by_desc(A));

    int top = M;
    for (int i = 1; i <= K; i++) {
        auto& [idx, A, B, C] = queries[i];

        while (top > 0 and A < top) {
            int x = rounds[top--];
            disjointSet.unionParent(x, parent[x]);
        }

        ans[idx] = disjointSet.isConnected(B, C);
    }

    for (int i = 1; i <= K; i++)
        cout << (ans[i] ? "Same Same;" : "No;") << '\n';

    return 0;
}