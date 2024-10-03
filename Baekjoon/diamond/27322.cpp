#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}


constexpr int INF = 10;

struct Node {
    int count[11], min, max;
    ll sum;
    int minLazy, maxLazy, addLazy;
} tree[1 << 19];
int arr[500001];


Node merge(Node n1, Node n2) {
    Node ret;

    for (int i = 1; i <= 10; i++) {
        ret.count[i] = n1.count[i] + n2.count[i];
    }

    ret.min = min(n1.min, n2.min);
    ret.max = max(n1.max, n2.max);
    ret.sum = n1.sum + n2.sum;

    ret.minLazy = INF;
    ret.maxLazy = 1;
    ret.addLazy = 0;

    return ret;
}

void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = {
            {0,}, // count
            arr[start], // min
            arr[start], // max
            arr[start], // sum
            INF, // minLazy
            1, // maxLazy
            0// addLazy
        };
        if (arr[start] <= 10) tree[node].count[arr[start]] = 1;
        return;
    }
    init(node*2, start, (start+end)/2);
    init(node*2+1, (start+end)/2+1, end);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}


void refresh(int node, int start, int end, int query, int x) {
    if (query == 1) {
        tree[node].min = min(tree[node].min, x);
        tree[node].max = min(tree[node].max, x);

        if (x < 1) {
            tree[node].sum = (end - start + 1) * x;
            fill(tree[node].count, tree[node].count + 11, 0);
        } else {
            int moreTen = (end - start + 1);
            for (int i = 1; i <= 10; i++) {
                moreTen -= tree[node].count[i];
            }
            tree[node].count[x] += moreTen;
            for (int i = x+1; i <= 10; i++) {
                tree[node].count[x] += tree[node].count[i];
                tree[node].count[i] = 0;
            }
            tree[node].sum = 0;
            for (int i = 1; i <= 10; i++) {
                tree[node].sum += i * tree[node].count[i];
            }
        }
    } else if (query == 2) {
        tree[node].min = max(tree[node].min, x);
        tree[node].max = max(tree[node].max, x);

        if (x < 1) {
            return;
        } else {
            for (int i = x-1; 1 <= i; i--) {
                tree[node].sum += (x - i) * tree[node].count[i];
                tree[node].count[x] += tree[node].count[i];
                tree[node].count[i] = 0;
            }
        }
    } else {
        tree[node].min += x;
        tree[node].max += x;
        tree[node].sum += (end - start + 1) * x;

        if (x <= 10) {
            for (int i = 10; 1 <= i; i--) {
                if (i + x <= 10) tree[node].count[i+x] += tree[node].count[i];
                tree[node].count[i] = 0;
            }
        } else {
            fill(tree[node].count, tree[node].count+11, 0);
        }
    }
}

void update(int node, int query, int x) {
    if (query == 1) {
        tree[node].minLazy = min(tree[node].minLazy, x-tree[node].addLazy);
        tree[node].maxLazy = min(tree[node].maxLazy, x-tree[node].addLazy);
    } else if (query == 2) {
        tree[node].minLazy = max(tree[node].minLazy, x-tree[node].addLazy);
        tree[node].maxLazy = max(tree[node].maxLazy, x-tree[node].addLazy);
    } else { // query == 3
        tree[node].addLazy += x;
        if (tree[node].minLazy != INF)
            tree[node].minLazy -= x;
        if (tree[node].maxLazy != 1)
            tree[node].maxLazy -= x;
    }
}

void propagate(int node, int start, int end) {
    if (tree[node].minLazy != INF) {
        refresh(node, start, end, 1, tree[node].minLazy);
        if (start != end) {
            update(node*2, 1, tree[node].minLazy);
            update(node*2+1, 1, tree[node].minLazy);
        }
        tree[node].minLazy = INF;
    }
    if (tree[node].maxLazy != 1) {
        refresh(node, start, end, 2, tree[node].maxLazy);
        if (start != end) {
            update(node*2, 2, tree[node].maxLazy);
            update(node*2+1, 2, tree[node].maxLazy);
        }
        tree[node].maxLazy = 1;
    }
    if (tree[node].addLazy != 0) {
        refresh(node, start, end, 3, tree[node].addLazy);
        if (start != end) {
            update(node*2, 3, tree[node].addLazy);
            update(node*2+1, 3, tree[node].addLazy);
        }
        tree[node].addLazy = 0;
    }
}

void rangeUpdate(int node, int start, int end, int left, int right, int query, int x) {
    propagate(node, start, end);
    if (right < start or end < left) return;
    if (left <= start and end <= right) {
        update(node, query, x);
        propagate(node, start, end);
        return;
    }
    rangeUpdate(node*2, start, (start+end)/2, left, right, query, x);
    rangeUpdate(node*2+1, (start+end)/2+1, end, left, right, query, x);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}

ll getRange(int node, int start, int end, int left, int right, int query) {
    propagate(node, start, end);
    if (right < start or end < left) {
        if (query == 4) return INF;
        else if (query == 5) return 1;
        else return 0;
    }
    if (left <= start and end <= right) {
        if (query == 4) return tree[node].min;
        else if (query == 5) return tree[node].max;
        else return tree[node].sum;
    }
    ll l = getRange(node*2, start, (start+end)/2, left, right, query);
    ll r = getRange(node*2+1, (start+end)/2+1, end, left, right, query);
    if (query == 4) return min(l, r);
    else if (query == 5) return max(l, r);
    else return l + r;
}


int main() {
    fastio();

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    init(1, 1, n);

    int m;
    cin >> m;
    while (m--) {
        int query, left, right;
        cin >> query >> left >> right;

        if (query <= 3) {
            int x;
            cin >> x;
            rangeUpdate(1, 1, n, left, right, query, x);
        } else {
            cout << getRange(1, 1, n, left, right, query) << '\n';
        }
    }

    return 0;
}