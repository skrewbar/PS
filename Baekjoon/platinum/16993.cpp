#include <bits/stdc++.h>
using namespace std;


class Node {
public:
    int lmax = -100000000, rmax = -100000000, lrmax = -100000000, sum = 0;
    Node() = default;
    Node(int elem) : lmax(elem), rmax(elem), lrmax(elem), sum(elem) {}
    Node(int l, int r, int lr, int s) : lmax(l), rmax(r), lrmax(lr), sum(s) {}

    friend Node operator+(const Node &l, const Node &r) {
        return Node(max(l.lmax, l.sum + r.lmax), max(l.rmax + r.sum, r.rmax), max({l.lrmax, l.rmax + r.lmax, r.lrmax}), l.sum + r.sum);
    }
};


class SegmentTree {
private:
    vector<Node> tree;
    int size;
public:
    SegmentTree(vector<int> &arr) {
        size = 1 << (int)ceil(log2(arr.size()));
        tree.resize(size << 1);
        
        for (int i = 0; i < arr.size(); i++) {
            tree[i + size] = Node(arr[i]);
        }

        for (int i = size-1; i > 0; i--) {
            tree[i] = tree[i<<1] + tree[i<<1|1];
        }
    }

    int get_max_continuous_sum(int l, int r) {
        Node lres, rres;
        for (l += size-1, r += size-1; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) lres = lres + tree[l++];
            if (~r & 1) rres = tree[r--] + rres;
        }
        return (lres + rres).lrmax;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree tree(arr);

    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << tree.get_max_continuous_sum(l, r) << '\n';
    }
}