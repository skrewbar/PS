#include <bits/stdc++.h>
using namespace std;

class ArraySeg {
private:
    vector<int> tree;
    int n;
public:
    ArraySeg(int n) : n(n) {
        tree.resize(n << 1);
    }

    void modify(int i, int value) {
        int j = i;
        for (tree[i+=n]=value; i > 1; i >>= 1) {
            tree[i>>1] = tree[i] + tree[i^1];
        }
    }

    int query(int l, int r) {
        int sum = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) sum += tree[l++];
            if (~r & 1) sum += tree[r--];
        }
        return sum;
    }
};

class TableSeg {
private:
    vector<ArraySeg> tree;
    int n;
public:
    TableSeg(int n) : n(n) {
        tree.resize(n << 1, ArraySeg(n));
    }

    void modify(int x, int y, int value) {
        for (tree[x+=n].modify(y, value); x > 1; x >>= 1) {
            int c1 = tree[x].query(y, y);
            int c2 = tree[x^1].query(y, y);
            tree[x>>1].modify(y, c1 + c2);
        }
    }

    int query(int lx, int rx, int ly, int ry) {
        int sum = 0;
        for (lx += n, rx += n; lx <= rx; lx >>= 1, rx >>= 1) {
            if (lx & 1) sum += tree[lx++].query(ly, ry);
            if (~rx & 1) sum += tree[rx--].query(ly, ry);
        }
        return sum;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    TableSeg tree(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v; cin >> v;
            tree.modify(i, j, v);
        }
    }

    while (m--) {
        int w; cin >> w;

        if (w == 0) {
            int x, y, c;
            cin >> x >> y >> c;
            tree.modify(x-1, y-1, c);
        } else {
            int lx, ly, rx, ry;
            cin >> lx >> ly >> rx >> ry;
            cout << tree.query(lx-1, rx-1, ly-1, ry-1) << '\n';
        }
    }
}