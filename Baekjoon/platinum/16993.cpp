#include <bits/stdc++.h>
using namespace std;

int n, m;
struct Node {
    ll lmax, rmax, mx, sum;
} tree[400000];
ll arr[100000];


Node merge(Node l, Node r) {
    Node ret;
    ret.lmax = max(l.lmax, l.sum + r.lmax);
    ret.rmax = max(r.rmax, l.rmax + r.sum);
    ret.mx = max({ret.lmax, ret.rmax, l.mx, r.mx});
    return ret;
}


void init(int node = 1, int start = 0, int end = n-1) {
    if (start == end) {
        tree[node] = {arr[start], arr[end], arr[start], arr[end]};
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}