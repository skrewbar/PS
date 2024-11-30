#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Node {
public:
    ll lmax, rmax, lrmax, sum;

    Node() {}
    Node(ll l, ll r, ll lr, ll s) : lmax(l), rmax(r), lrmax(lr), sum(s) {}

    void operator+=(const ll &v) {
        lmax = rmax = lrmax = sum += v;
    }

    static Node merge(const Node &l, const Node &r) {
        return {max(l.lmax, l.sum + r.lmax), max(l.rmax + r.sum, r.rmax), max({l.lrmax, l.rmax + r.lmax, r.lrmax}), l.sum + r.sum};
    }
};

class SegmentTree {
private:
    int size;
    vector<Node> tree;
public:
    SegmentTree(int size) {
        size = 1 << (int)ceil(log2(size));
        this->size = size;
        tree.resize(size << 1);
    }

    void reset() {
        tree.assign(tree.size(), {0, 0, 0, 0});
    }

    void add(int index, ll value) {
        index |= size;
        tree[index] += value;
        while (index >>= 1) tree[index] = Node::merge(tree[index << 1], tree[index << 1 | 1]);
    }

    ll max() {
        return tree[1].lrmax;
    }
};

class Mine {
public:
    ll x, y, w;
    bool operator<(const Mine &m) {
        if (y == m.y) return x < m.x;
        return y < m.y;
    }
};

template <typename T>
void compress(vector<T> &arr) {
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> unique_x(n);
    vector<ll> unique_y(n);
    vector<Mine> mines(n);

    for (int i = 0; i < n; i++) {
        cin >> mines[i].x >> mines[i].y >> mines[i].w;
        unique_x[i] = mines[i].x;
        unique_y[i] = mines[i].y;
    }
    compress(unique_x);
    compress(unique_y);

    for (int i = 0; i < n; i++) {
        mines[i].x = lower_bound(unique_x.begin(), unique_x.end(), mines[i].x) - unique_x.begin();
        mines[i].y = lower_bound(unique_y.begin(), unique_y.end(), mines[i].y) - unique_y.begin();
    }

    sort(mines.begin(), mines.end());
    SegmentTree tree(unique_x.size());
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 and mines[i-1].y == mines[i].y) continue;
        tree.reset();
        for (int j = i; j < n; j++) {
            tree.add(mines[j].x, mines[j].w);
            if (j == n-1 or mines[j].y != mines[j+1].y) ans = max(tree.max(), ans);
        }
    }
    cout << ans;
}