#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

enum Query : uint8_t {
    ADD = 1,
    MUL = 2,
    SET = 3,
    SUM = 4,
};

struct SegmentTree {
    struct Lazy {
        ll add = 0, mul = 1;
    };

    struct Node {
        Lazy lazy;
        ll sum;

        Node() = default;
        Node(ll v) : sum(v) {}

        Node operator+(const Node& node) const {
            return Node((sum + node.sum) % MOD);
        }

        void operator+=(ll v) { lazy.add = (lazy.add + v) % MOD; }

        void operator*=(ll v) {
            lazy.add = (lazy.add * v) % MOD;
            lazy.mul = (lazy.mul * v) % MOD;
        }
    };

    vector<Node> tree;

    SegmentTree(const vector<ll>& arr) {
        int height = (int)ceil(log2(arr.size())) + 1;
        tree = vector<Node>(1 << height);
        init(arr, 1, 0, arr.size() - 1);
    }

    void init(const vector<ll>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = Node(arr[start]);
            return;
        }

        int mid = (start + end) / 2;
        init(arr, node << 1, start, mid);
        init(arr, node << 1 | 1, mid + 1, end);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    void propagate(int node, int start, int end) {
        Node& n = tree[node];
        Lazy& lazy = tree[node].lazy;

        n.sum = (n.sum * lazy.mul) % MOD + lazy.add * (end - start + 1) % MOD;
        n.sum %= MOD;

        if (start != end) {
            tree[node << 1] *= lazy.mul;
            tree[node << 1] += lazy.add;
            tree[node << 1 | 1] *= lazy.mul;
            tree[node << 1 | 1] += lazy.add;
        }

        lazy = Lazy();
    }

    void update(int node,
                int start,
                int end,
                int left,
                int right,
                ll v,
                Query query) {
        propagate(node, start, end);

        if (end < left or right < start)
            return;
        if (left <= start and end <= right) {
            if (query == ADD)
                tree[node] += v;
            else if (query == MUL)
                tree[node] *= v;
            else {
                tree[node] *= 0;
                tree[node] += v;
            }
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        update(node << 1, start, mid, left, right, v, query);
        update(node << 1 | 1, mid + 1, end, left, right, v, query);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    ll getRangeSum(int node, int start, int end, int left, int right) {
        propagate(node, start, end);

        if (end < left or right < start)
            return 0;
        if (left <= start and end <= right)
            return tree[node].sum;

        int mid = (start + end) / 2;
        ll lsum = getRangeSum(node << 1, start, mid, left, right),
           rsum = getRangeSum(node << 1 | 1, mid + 1, end, left, right);
        return (lsum + rsum) % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    SegmentTree tree(arr);

    int m;
    cin >> m;
    while (m--) {
        int q, x, y;
        cin >> q >> x >> y;
        x--, y--;

        if (q == ADD) {
            ll v;
            cin >> v;
            tree.update(1, 0, n - 1, x, y, v, Query(q));
        } else if (q == MUL) {
            ll v;
            cin >> v;
            tree.update(1, 0, n - 1, x, y, v, Query(q));
        } else if (q == SET) {
            ll v;
            cin >> v;
            tree.update(1, 0, n - 1, x, y, v, Query(q));
        } else {
            cout << tree.getRangeSum(1, 0, n - 1, x, y) << '\n';
        }
    }

    return 0;
}