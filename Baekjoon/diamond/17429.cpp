#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using uint = unsigned int;

struct Query {
    uint add = 0, mul = 1;
};

struct SegmentTree {
    vector<uint> tree;
    vector<Query> lazy;

    SegmentTree(size_t n) {
        int height = ceil(log2(n));
        tree.resize(1 << (height + 1));
        lazy.resize(1 << (height + 1));
    }

    void propagate(int node, int start, int end) {
        tree[node] *= lazy[node].mul;
        tree[node] += lazy[node].add * (end - start + 1);

        if (start != end) {
            lazy[node << 1].mul *= lazy[node].mul;
            lazy[node << 1].add *= lazy[node].mul;
            lazy[node << 1].add += lazy[node].add;

            lazy[node << 1 | 1].mul *= lazy[node].mul;
            lazy[node << 1 | 1].add *= lazy[node].mul;
            lazy[node << 1 | 1].add += lazy[node].add;
        }

        lazy[node] = Query();
    }

    void modify(int node, int start, int end, int left, int right, Query q) {
        propagate(node, start, end);

        if (right < start or end < left)
            return;

        if (left <= start and end <= right) {
            lazy[node] = q;
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) >> 1;
        modify(node << 1, start, mid, left, right, q);
        modify(node << 1 | 1, mid + 1, end, left, right, q);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    uint getRangeSum(int node, int start, int end, int left, int right) {
        propagate(node, start, end);

        if (right < start or end < left)
            return 0;

        if (left <= start and end <= right)
            return tree[node];

        int mid = (start + end) >> 1;
        uint lsum = getRangeSum(node << 1, start, mid, left, right);
        uint rsum = getRangeSum(node << 1 | 1, mid + 1, end, left, right);
        return lsum + rsum;
    }
};

vector<int> adj[505050];
int parent[505050], depth[505050], sz[505050], in[505050], out[505050],
    top[505050];

void initHeavyEdge(int node) {
    sz[node] = 1;

    for (int child : adj[node]) {
        if (child == parent[node])
            continue;

        parent[child] = node;
        depth[child] = depth[node] + 1;
        initHeavyEdge(child);
        sz[node] += sz[child];
    }

    for (int& child : adj[node]) {
        if (child == parent[node])
            continue;

        if (sz[child] > sz[adj[node][0]])
            swap(child, adj[node][0]);
    }
}

void initHLD(int node) {
    static int visitedCnt = 0;

    in[node] = visitedCnt++;

    for (int child : adj[node]) {
        if (child == parent[node])
            continue;

        top[child] = (child == adj[node][0] ? top[node] : child);
        initHLD(child);
    }

    out[node] = visitedCnt - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N - 1; i++) {
        int s, e;
        cin >> s >> e;

        adj[s].push_back(e);
        adj[e].push_back(s);
    }

    initHeavyEdge(1);
    top[1] = 1;
    initHLD(1);

    SegmentTree segTree(N);

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1 or type == 3) {
            int x;
            uint v;

            cin >> x >> v;

            Query q;
            if (type == 1)
                q.add = v;
            else
                q.mul = v;

            segTree.modify(1, 0, N - 1, in[x], out[x], q);
        } else if (type == 2 or type == 4) {
            int x, y;
            uint v;

            cin >> x >> y >> v;

            Query q;
            if (type == 2)
                q.add = v;
            else
                q.mul = v;

            while (top[x] != top[y]) {
                if (depth[top[x]] > depth[top[y]])
                    swap(x, y);

                segTree.modify(1, 0, N - 1, in[top[y]], in[y], q);
                y = parent[top[y]];
            }
            if (depth[x] > depth[y])
                swap(x, y);

            segTree.modify(1, 0, N - 1, in[x], in[y], q);
        } else if (type == 5) {
            int x;
            cin >> x;

            cout << segTree.getRangeSum(1, 0, N - 1, in[x], out[x]) << '\n';
        } else {
            int x, y;
            cin >> x >> y;

            uint ret = 0;

            while (top[x] != top[y]) {
                if (depth[top[x]] > depth[top[y]])
                    swap(x, y);

                ret += segTree.getRangeSum(1, 0, N - 1, in[top[y]], in[y]);
                y = parent[top[y]];
            }
            if (depth[x] > depth[y])
                swap(x, y);

            ret += segTree.getRangeSum(1, 0, N - 1, in[x], in[y]);
            cout << ret << '\n';
        }
    }

    return 0;
}