#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int _n) : n(_n), t(_n << 1, 1) {}

    void modify(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1)
            t[i >> 1] = min(t[i], t[i ^ 1]);
    }

    int getRangeMin(int l, int r) {
        int ret = INT_MAX;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = min(ret, t[l++]);
            if (~r & 1)
                ret = min(ret, t[r--]);
        }

        return ret;
    }
};

int parent[200'200], sz[200'2000], depth[200'200], in[200'200], top[200'200];
vector<int> childs[200'200];

void initHLD(int node) {
    sz[node] = 1;
    for (int& child : childs[node]) {
        depth[child] = depth[node] + 1;
        initHLD(child);
        sz[node] += sz[child];

        if (sz[child] > sz[childs[node].front()])
            swap(child, childs[node].front());
    }
}

void initTour(int node) {
    static int visitedCnt = 0;

    in[node] = visitedCnt++;

    for (int child : childs[node]) {
        top[child] = (child == childs[node].front() ? top[node] : child);
        initTour(child);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    for (int i = 2; i <= N; i++) {
        cin >> parent[i];
        childs[parent[i]].push_back(i);
    }

    initHLD(1);
    top[1] = 1;
    initTour(1);

    SegmentTree tree(N);
    while (Q--) {
        int b, c, d;
        cin >> b >> c >> d;

        int u = b, v = c;
        int connected = 1;
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]])
                swap(u, v);

            connected = min(connected, tree.getRangeMin(in[top[v]], in[v]));
            v = parent[top[v]];
        }

        if (depth[u] > depth[v])
            swap(u, v);
        connected = min(connected, tree.getRangeMin(in[u] + 1, in[v]));

        if (b == c)
            connected = 1;

        if (connected) {
            cout << "YES\n";
            if (d == 1)
                tree.modify(in[b], 0);
        } else {
            cout << "NO\n";
            if (d == 1)
                tree.modify(in[c], 0);
        }
    }

    return 0;
}