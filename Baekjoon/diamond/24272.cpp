#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct SegmentTree {
    int n;
    vector<int> cnt, tree;

    SegmentTree(int _n): n(_n) {
        int size = 1 << (int)(ceil(log2(n)) + 1);
        cnt.resize(size);
        tree.resize(size);
    }

    void update(int node, int start, int end, int left, int right, int value) {
        if (end < left or right < start)
            return;
        if (left <= start and end <= right)
            cnt[node] += value;
        else {
            int mid = (start + end) / 2;
            update(node << 1, start, mid, left, right, value);
            update(node << 1 | 1, mid + 1, end, left, right, value);
        }

        if (cnt[node])
            tree[node] = end - start + 1;
        else if (start != end)
            tree[node] = tree[node << 1] + tree[node << 1 | 1];
        else
            tree[node] = 0;
    }

    void cover(int left, int right) {
        if (left > right)
            return;
        update(1, 0, n - 1, left, right, 1);
    }
    void uncover(int left, int right) {
        if (left > right)
            return;
        update(1, 0, n - 1, left, right, -1);
    }

    int getCoveredCnt() { return tree[1]; }
};

vector<int> adj[101010];
int in[101010], out[101010], sz[101010];

void eulerTour(int node, int parent) {
    static int visitedCnt = 0;

    in[node] = visitedCnt++;
    sz[node] = 1;

    for (int child : adj[node]) {
        if (child == parent)
            continue;

        eulerTour(child, node);
        sz[node] += sz[child];
    }

    out[node] = visitedCnt - 1;
}

set<pair<int, int>> directedEdges;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int U, V;
        string D;

        cin >> U >> D >> V;

        adj[U].push_back(V);
        adj[V].push_back(U);

        if (D[0] == '<')
            directedEdges.emplace(V, U);
        else if (D[1] == '>')
            directedEdges.emplace(U, V);
    }

    eulerTour(1, 0);

    SegmentTree segTree(N);

    auto directEdge = [&](pair<int, int> edge) {
        auto [u, v] = edge;

        if (in[u] < in[v]) {
            segTree.cover(in[v], out[v]);
        } else {
            segTree.cover(in[1], in[u] - 1);
            segTree.cover(out[u] + 1, out[1]);
        }
    };
    auto undirectEdge = [&](pair<int, int> edge) {
        auto [u, v] = edge;

        if (in[u] < in[v]) {
            segTree.uncover(in[v], out[v]);
        } else {
            segTree.uncover(in[1], in[u] - 1);
            segTree.uncover(out[u] + 1, out[1]);
        }
    };

    for (auto edge : directedEdges)
        directEdge(edge);

    int Q;
    cin >> Q;
    while (Q--) {
        int u, v;
        string d;

        cin >> u >> d >> v;

        if (directedEdges.erase(pair(u, v))) {
            undirectEdge(pair(u, v));
        } else if (directedEdges.erase(pair(v, u))) {
            undirectEdge(pair(v, u));
        }

        if (d[0] == '<') {
            directEdge(pair(v, u));
            directedEdges.emplace(v, u);
        } else if (d[1] == '>') {
            directEdge(pair(u, v));
            directedEdges.emplace(u, v);
        }
        
        println("{}", N - segTree.getCoveredCnt());
    }

    return 0;
}