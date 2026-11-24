#include <bits/stdc++.h>
using namespace std;

int tree[400000];
int lazy[400000];


void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = 1 << 1;
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = tree[node*2] | tree[node*2+1];
    }
}


void updateLazy(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] = lazy[node];
        if (start != end) {
            lazy[node*2] = lazy[node];
            lazy[node*2+1] = lazy[node];
        }
        lazy[node] = 0;
    }
}


int getColors(int node, int start, int end, int left, int right) {
    updateLazy(node, start, end);
    if (right < start or end < left) {
        return 0;
    }
    if (left <= start and end <= right) {
        return tree[node];
    }
    int lColors = getColors(node*2, start, (start+end)/2, left, right);
    int rColors = getColors(node*2+1, (start+end)/2+1, end, left, right);
    return lColors | rColors;
}


void update(int node, int start, int end, int left, int right, int color) {
    updateLazy(node, start, end);
    if (right < start or end < left) {
        return;
    }
    if (left <= start and end <= right) {
        lazy[node] = 1 << color;
        updateLazy(node, start, end);
        return;
    }
    update(node*2, start, (start+end)/2, left, right, color);
    update(node*2+1, (start+end)/2+1, end, left, right, color);
    tree[node] = tree[node*2] | tree[node*2+1];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(tree, tree+400000, 0);
    fill(lazy, lazy+400000, 0);
    int n, t, q;
    cin >> n >> t >> q;

    init(1, 0, n-1);
    while (q--) {
        char cmd;
        cin >> cmd;

        int left, right;
        cin >> left >> right;
        if (right < left) swap(left, right);

        if (cmd == 'C') {
            int color;
            cin >> color;
            update(1, 0, n-1, left-1, right-1, color);
        } else {
            int colors = getColors(1, 0, n-1, left-1, right-1);
            int ans = 0;
            for (int i = 1 ; i <= t ; i++) {
                if (colors & (1 << i)) ans++;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}