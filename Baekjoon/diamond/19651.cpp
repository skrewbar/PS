#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll lvalue, rvalue, lmax, rmax, lazy, mmax;
} tree[400010];

int n, m;
ll a[100010];
ll b[100010];

Node merge(Node l, Node r) {
    if (l.mmax == 0) return r;
    if (r.mmax == 0) return l;

    Node ret = {l.lvalue, r.rvalue, l.lmax, r.rmax, 0, max(l.mmax, r.mmax)};

    if (l.rvalue == r.lvalue) {
        if (l.lmax == l.mmax) {
            ret.lmax += r.lmax;
        }
        if (r.rmax == r.mmax) {
            ret.rmax += l.rmax;
        }
        ret.mmax = max({ret.mmax, l.rmax + r.lmax});
    }
    ret.mmax = max({ret.mmax, ret.lmax, ret.rmax});

    return ret;
}


void init(int node = 1, int start = 0, int end = n-2) {
    if (start == end) {
        tree[node] = {b[start], b[end], 1, 1, 0, 1};
    }
    else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}


void updateLazy(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        tree[node].lvalue += tree[node].lazy;
        tree[node].rvalue += tree[node].lazy;
        if (start != end) {
            tree[node*2].lazy += tree[node].lazy;
            tree[node*2+1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }
}


void addRange(int node, int start, int end, int left, int right, int value) {
    updateLazy(node, start, end);
    if (right < start or end < left) return;
    if (left <= start and end <= right) {
        tree[node].lazy += value;
        updateLazy(node, start, end);
        return;
    }
    addRange(node*2, start, (start+end)/2, left, right, value);
    addRange(node*2+1, (start+end)/2+1, end, left, right, value);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}


Node find(int node, int start, int end, int left, int right) {
    updateLazy(node, start, end);
    if (right < start or end < left) return {0, 0, 0, 0, 0, 0};
    if (left <= start and end <= right) return tree[node];

    Node l = find(node*2, start, (start+end)/2, left, right);
    Node r = find(node*2+1, (start+end)/2+1, end, left, right);
    return merge(l, r);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    for (int i = 0 ; i < n - 1 ; i++) {
        b[i] = a[i+1] - a[i];
    }
    init();

    cin >> m;
    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {
            int left, right;
            ll x, y;
            cin >> left >> right >> x >> y;
            left--; right--;

            addRange(1, 0, n-2, left-1, left-1, x);
            addRange(1, 0, n-2, right, right, -(x + y * (right - left)));
            addRange(1, 0, n-2, left, right-1, y);
        } else {
            int left, right;
            cin >> left >> right;
            left--; right--;

            cout << find(1, 0, n-2, left, right-1).mmax + 1 << '\n';
        }
    }
}