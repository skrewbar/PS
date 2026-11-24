#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

using ll = long long;

class SegmentTree {
   public:
    int n;
    vector<ll> tree, lazy;

    SegmentTree(int _n) : n(_n) {
        int sz = 1 << ((int)ceil(log2(n)) + 1);

        tree.resize(sz);
        lazy.resize(sz);
    }

    void add(int left, int right, ll value) {
        add(1, 0, n - 1, left, right, value);
    }

    ll getRangeSum(int left, int right) {
        return getRangeSum(1, 0, n - 1, left, right);
    }

   private:
    void propagate(int node, int start, int end) {
        tree[node] += lazy[node];

        if (start != end) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    void add(int node, int start, int end, int left, int right, ll value) {
        propagate(node, start, end);

        if (end < left or right < start)
            return;
        if (left <= start and end <= right) {
            lazy[node] += value;
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        add(node << 1, start, mid, left, right, value);
        add(node << 1 | 1, mid + 1, end, left, right, value);

        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    ll getRangeSum(int node, int start, int end, int left, int right) {
        propagate(node, start, end);

        if (end < left or right < start)
            return 0;
        if (left <= start and end <= right)
            return tree[node];

        int mid = (start + end) / 2;
        ll leftSum = getRangeSum(node << 1, start, mid, left, right);
        ll rightSum = getRangeSum(node << 1 | 1, mid + 1, end, left, right);

        return leftSum + rightSum;
    }
};

vector<int> adj[101010];
int depth[101010], parent[101010], sz[101010], in[101010], out[101010],
    top[101010];

void preprocessHLD(int at) {
    for (int& child : adj[at]) {
        if (child == parent[at]) {
            swap(adj[at].back(), child);
            adj[at].pop_back();
            break;
        }
    }

    sz[at] = 1;
    for (int child : adj[at]) {
        depth[child] = depth[at] + 1;
        parent[child] = at;
        preprocessHLD(child);

        sz[at] += sz[child];
    }
}

void heavyLightDecompose(int at) {
    static int counter = 0;

    in[at] = counter++;

    for (int& child : adj[at]) {
        if (sz[child] > sz[adj[at].front()])
            swap(child, adj[at].front());
    }

    for (int child : adj[at]) {
        top[child] = (child == adj[at].front() ? top[at] : child);
        heavyLightDecompose(child);
    }

    out[at] = counter - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    preprocessHLD(1);
    top[1] = 1;
    heavyLightDecompose(1);

    SegmentTree segTree(N);

    for (int i = 0; i < M; i++) {
        char type;
        int u, v;
        cin >> type >> u >> v;

        if (type == 'P') {
            while (top[u] != top[v]) {
                if (depth[top[u]] > depth[top[v]])
                    swap(u, v);

                segTree.add(in[top[v]], in[v], 1);
                v = parent[top[v]];
            }

            if (depth[u] > depth[v])
                swap(u, v);
            segTree.add(in[u] + 1, in[v], 1);
        } else {
            ll ans = 0;
            while (top[u] != top[v]) {
                if (depth[top[u]] > depth[top[v]])
                    swap(u, v);

                ans += segTree.getRangeSum(in[top[v]], in[v]);
                v = parent[top[v]];
            }

            if (depth[u] > depth[v])
                swap(u, v);
            ans += segTree.getRangeSum(in[u] + 1, in[v]);

            println("{}", ans);
        }
    }

    return 0;
}