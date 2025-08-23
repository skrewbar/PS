#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

// Segment Tree
struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int size) : n(size), t(size << 1) {}

    void modify(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    int getRangeSum(int l, int r) {
        int ret = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret += t[l++];
            if (~r & 1)
                ret += t[r--];
        }

        return ret;
    }
};

// Disjoint Set
struct DisjointSet {
    vector<int> parent;

    DisjointSet(int size) : parent(size) {
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int findRoot(int x) {
        if (x != parent[x])
            parent[x] = findRoot(parent[x]);
        return parent[x];
    }

    void unionRoot(int u, int v) { parent[findRoot(u)] = findRoot(v); }

    bool connected(int u, int v) { return findRoot(u) == findRoot(v); }
};

// Heavy-light Decomposition
vector<int> parent, sz, depth, in, top, penguinCnt;
vector<vector<int>> adj;
vector<bool> initialized;

void initHLD(int node) {
    initialized[node] = true;

    for (int& child : adj[node]) {
        if (child != parent[node])
            continue;

        swap(child, adj[node].back());
        adj[node].pop_back();
        break;
    }

    sz[node] = 1;
    for (int& child : adj[node]) {
        depth[child] = depth[node] + 1;
        parent[child] = node;
        initHLD(child);
        sz[node] += sz[child];

        if (sz[child] > sz[adj[node].front()])
            swap(child, adj[node].front());
    }
}

void initTour(int node) {
    static int visitedCnt = 0;
    in[node] = ++visitedCnt;

    for (int child : adj[node]) {
        top[child] = (child == adj[node].front() ? top[node] : child);
        initTour(child);
    }
}

// Queries
enum QueryType : uint8_t {
    BRIDGE,
    PENGUINS,
    EXCURSION,
};
struct Query {
    QueryType type;
    int args[2];
};
vector<Query> queries;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    parent = sz = depth = in = top = penguinCnt = vector<int>(N + 1);
    adj.resize(N + 1);
    initialized.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> penguinCnt[i];

    int Q;
    cin >> Q;
    queries.resize(Q);
    DisjointSet disjointSet(N + 1);
    for (Query& q : queries) {
        string type;
        cin >> type >> q.args[0] >> q.args[1];

        if (type == "bridge") {
            q.type = BRIDGE;
            auto [A, B] = q.args;
            if (not disjointSet.connected(A, B)) {
                adj[A].push_back(B);
                adj[B].push_back(A);
                disjointSet.unionRoot(A, B);
            }
        } else if (type == "penguins")
            q.type = PENGUINS;
        else /* if (type == "excursion") */
            q.type = EXCURSION;
    }

    for (int i = 1; i <= N; i++) {
        if (not initialized[i]) {
            initHLD(i);
            top[i] = i;
            initTour(i);
        }
    }

    SegmentTree segTree(N + 1);
    for (int i = 1; i <= N; i++) {
        segTree.modify(in[i], penguinCnt[i]);
    }

    disjointSet = DisjointSet(N + 1);
    for (Query q : queries) {
        switch (q.type) {
            case BRIDGE: {
                auto [A, B] = q.args;
                println("{}", disjointSet.connected(A, B) ? "no" : "yes");
                disjointSet.unionRoot(A, B);
                break;
            }
            case PENGUINS: {
                auto [A, X] = q.args;
                segTree.modify(in[A], X);
                break;
            }
            case EXCURSION: {
                auto [A, B] = q.args;
                if (not disjointSet.connected(A, B)) {
                    println("impossible");
                    break;
                }

                int ans = 0;
                while (top[A] != top[B]) {
                    if (depth[top[A]] > depth[top[B]])
                        swap(A, B);
                    ans += segTree.getRangeSum(in[top[B]], in[B]);
                    B = parent[top[B]];
                }
                if (depth[A] > depth[B])
                    swap(A, B);
                ans += segTree.getRangeSum(in[A], in[B]);
                println("{}", ans);
                break;
            };
        }
    }

    return 0;
}