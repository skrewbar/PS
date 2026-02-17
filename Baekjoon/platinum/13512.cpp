#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int _n) : n(1 << (int)ceil(log2(_n))), t(n << 1) {}

    void toggleColor(int i) {
        for (t[i += n] ^= 1; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    int getRangeSum(int l, int r) {
        int sum = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                sum += t[l++];
            if (~r & 1)
                sum += t[r--];
        }

        return sum;
    }

    int getFirst(int l, int r) {
        if (getRangeSum(l, r) == 0)
            return -1;

        while (l < r) {
            int m = (l + r) / 2;

            if (getRangeSum(l, m))
                r = m;
            else
                l = m + 1;
        }

        return l;
    }
};

vector<int> adj[101010];
int parent[101010], in[101010], invIn[101010], out[101010], sz[101010], top[101010];

void preprocessHLD(int at) {
    sz[at] = 1;

    // remove the parent from adjacency list
    for (int& child : adj[at]) {
        if (child == parent[at]) {
            swap(adj[at].back(), child);
            adj[at].pop_back();
            break;
        }
    }

    for (int child : adj[at]) {
        parent[child] = at;
        preprocessHLD(child);
        sz[at] += sz[child];
    }
}

void heavyLightDecomposition(int at) {
    static int counter = 0;

    in[at] = counter++;
    invIn[in[at]] = at;

    for (int& child : adj[at]) {
        if (sz[child] > sz[adj[at].front()])
            swap(child, adj[at].front());
    }

    for (int child : adj[at]) {
        top[child] = (child == adj[at].front() ? top[at] : child);
        heavyLightDecomposition(child);
    }

    out[at] = counter - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    parent[1] = 0;
    preprocessHLD(1);
    top[1] = 1;
    heavyLightDecomposition(1);

    SegmentTree segTree(N);

    int M;
    cin >> M;
    while (M--) {
        int type, v;
        cin >> type >> v;

        if (type == 1) {
            segTree.toggleColor(in[v]);
        } else {
            int minBlack = -1;
            while (v > 0) {
                int query = segTree.getFirst(in[top[v]], in[v]);
                if (query != -1)
                    minBlack = invIn[query];
                v = parent[top[v]];
            }
            println("{}", minBlack);
        }
    }

    return 0;
}