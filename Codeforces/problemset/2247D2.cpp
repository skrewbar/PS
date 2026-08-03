#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 2e9;

struct SegmentTree {
    struct Node {
        int minValue, maxValue;
        int minK;
    };

    vector<Node> tree;

    SegmentTree(int n) {
        int height = 33 - __builtin_clz(n - 1);
        tree.assign(1 << height, {INF, INF, 0});
    }

    void change(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = {value, value, 0};
            return;
        }

        int mid = (start + end) / 2;
        if (index <= mid) change(node << 1, start, mid, index, value);
        else change(node << 1 | 1, mid + 1, end, index, value);

        if (tree[node << 1].maxValue > tree[node << 1 | 1].minValue)
            tree[node].minK = (end - start + 1) / 2;
        else tree[node].minK = max(tree[node << 1].minK, tree[node << 1 | 1].minK);

        tree[node].minValue = min(tree[node << 1].minValue, tree[node << 1 | 1].minValue);
        tree[node].maxValue = max(tree[node << 1].maxValue, tree[node << 1 | 1].maxValue);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    int paddedN = (n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 2);

    SegmentTree seg(paddedN);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        seg.change(1, 0, paddedN - 1, i, a);
    }

    cout << seg.tree[1].minK << '\n';

    while (q--) {
        int i, x;
        cin >> i >> x;

        seg.change(1, 0, paddedN - 1, i, x);

        cout << seg.tree[1].minK << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
