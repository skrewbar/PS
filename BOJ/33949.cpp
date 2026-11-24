#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

constexpr ll INF = 1LL << 50;

template <typename node_t>
struct SegmentTree {
    vector<node_t> t;
    size_t size;
    SegmentTree(size_t length) : t() {
        size = 1 << ((int)ceil(log2(length)));
        t = vector<node_t>(size << 1);

        for (int i = size; i < size + length; i++)
            t[i] = node_t(0);
        for (int i = size - 1; i > 0; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void add(int i, ll v) {
        t[i |= size] += v;
        for (i >>= 1; i > 0; i >>= 1)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
};

struct MaxNode {
    ll lmax = -INF, rmax = -INF, lrmax = -INF, sum = 0;

    MaxNode() = default;
    MaxNode(ll v) : lmax(v), rmax(v), lrmax(v), sum(v) {}

    void operator+=(ll v) {
        lmax += v;
        rmax += v;
        lrmax += v;
        sum += v;
    }

    MaxNode operator+(const MaxNode& node) {
        MaxNode ret;
        ret.lmax = max(lmax, sum + node.lmax);
        ret.rmax = max(rmax + node.sum, node.rmax);
        ret.lrmax = max({lrmax, rmax + node.lmax, node.lrmax});
        ret.sum = sum + node.sum;

        return ret;
    }
};
struct MinNode {
    ll lmin = INF, rmin = INF, lrmin = INF, sum = 0;

    MinNode() = default;
    MinNode(ll v) : lmin(v), rmin(v), lrmin(v), sum(v) {}

    void operator+=(ll v) {
        lmin += v;
        rmin += v;
        lrmin += v;
        sum += v;
    }

    MinNode operator+(const MinNode& node) {
        MinNode ret;
        ret.lmin = min(lmin, sum + node.lmin);
        ret.rmin = min(rmin + node.sum, node.rmin);
        ret.lrmin = min({lrmin, rmin + node.lmin, node.lrmin});
        ret.sum = sum + node.sum;

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, q;
    cin >> s >> q;

    SegmentTree<MaxNode> maxTree(s);
    SegmentTree<MinNode> minTree(s);
    while (q--) {
        int query;
        cin >> query;

        if (query == 1) {
            int a, b;
            cin >> a >> b;
            a--;

            maxTree.add(a, b);
            minTree.add(a, b);
        } else {
            if (minTree.t[1].sum == minTree.t[1].lrmin)
                cout << maxTree.t[1].lrmax << '\n';
            else
                cout << max(maxTree.t[1].lrmax,
                            minTree.t[1].sum - minTree.t[1].lrmin)
                     << '\n';
        }
    }
}