#include <bits/stdc++.h>
using namespace std;

using ll = long long;

enum Query {
    MIN = 1,
    MAX = 2,
    ADD = 3,
    GET_MIN = 4,
    GET_MAX = 5,
    GET_SUM = 6,
};

struct Node {
    array<int, 11> count;
    int minimum = 1e9, maximum = 1;
    ll sum = 0;
    int minLazy = 1e9, maxLazy = 1, addLazy = 0;

    Node() { ranges::fill(count, 0); };
    Node(int n) : minimum(n), maximum(n), sum(n) {
        ranges::fill(count, 0);
        if (1 <= n and n <= 10)
            count[n]++;
    }

    Node merge(const Node& node) {
        Node ret;
        for (int i = 1; i <= 10; i++)
            ret.count[i] = count[i] + node.count[i];

        ret.minimum = min(minimum, node.minimum);
        ret.maximum = max(maximum, node.maximum);
        ret.sum = sum + node.sum;
        return ret;
    }

    void resetLazy() {
        minLazy = 1e9;
        maxLazy = 1;
        addLazy = 0;
    }
};

struct SegmentTree {
    vector<Node> tree;

    SegmentTree(const vector<ll>& arr) {
        int height = (int)ceil(log2(arr.size())) + 1;
        tree = vector<Node>(1 << height);
        init(arr, 1, 0, arr.size() - 1);
    }

    void init(const vector<ll>& arr, int n, int s, int e) {
        if (s == e) {
            tree[n] = Node(arr[s]);
            return;
        }

        int mid = (s + e) / 2;
        init(arr, n << 1, s, mid);
        init(arr, n << 1 | 1, mid + 1, e);
        tree[n] = tree[n << 1].merge(tree[n << 1 | 1]);
    }

    void updateLazy(int n, Query q, int x) {
        if (q == MAX) {
            tree[n].minLazy = max(tree[n].minLazy, x - tree[n].addLazy);
            tree[n].maxLazy = max(tree[n].maxLazy, x - tree[n].addLazy);
        } else if (q == MIN) {
            tree[n].minLazy = min(tree[n].minLazy, x - tree[n].addLazy);
            tree[n].maxLazy = min(tree[n].maxLazy, x - tree[n].addLazy);
        } else {  // if (q == ADD)
            tree[n].addLazy += x;
        }
    }

    void applyLazy(int n, int s, int e) {
        Node& node = tree[n];
        int maxLazy = node.maxLazy, minLazy = node.minLazy,
            addLazy = node.addLazy;

        // 최대 쿼리
        if (maxLazy > 1) {
            for (int i = 0; i < maxLazy; i++) {
                node.count[maxLazy] += node.count[i];
                node.sum += (maxLazy - i) * node.count[i];
                node.count[i] = 0;
            }
            node.minimum = max(node.minimum, maxLazy);
            node.maximum = max(node.maximum, maxLazy);
        }

        // 최소 쿼리
        if (minLazy <= 0) {
            node.minimum = node.maximum = minLazy;
            node.sum = (e - s + 1) * minLazy;
            ranges::fill(node.count, 0);
        } else if (minLazy <= 10) {
            int bigger = (e - s + 1);
            for (int i = 1; i <= minLazy; i++)
                bigger -= node.count[i];

            node.count[minLazy] += bigger;

            for (int i = minLazy + 1; i <= 10; i++)
                node.count[i] = 0;

            node.minimum = min(node.minimum, minLazy);
            node.maximum = min(node.maximum, minLazy);
            node.sum = 0;
            for (int i = 1; i <= 10; i++)
                node.sum += i * node.count[i];
        }

        // 덧셈 쿼리
        if (addLazy > 0) {
            if (node.minimum > 0) {
                for (int i = max(10 - addLazy + 1, 1); i <= 10; i++)
                    node.count[i] = 0;
                for (int i = 10 - addLazy; i >= 1; i--) {
                    node.count[i + addLazy] += node.count[i];
                    node.count[i] = 0;
                }
            } else {
                if (node.minimum + addLazy <= 10)
                    node.count[node.minimum + addLazy] = (e - s + 1);
            }
            node.minimum += addLazy;
            node.maximum += addLazy;
            node.sum += (e - s + 1) * addLazy;
        }

        node.resetLazy();
    }
    void propagate(int n, int s, int e) {
        if (s != e) {
            updateLazy(n << 1, MAX, tree[n].maxLazy);
            updateLazy(n << 1 | 1, MAX, tree[n].maxLazy);
            updateLazy(n << 1, MIN, tree[n].minLazy);
            updateLazy(n << 1 | 1, MIN, tree[n].minLazy);
            updateLazy(n << 1, ADD, tree[n].addLazy);
            updateLazy(n << 1 | 1, ADD, tree[n].addLazy);
        }

        applyLazy(n, s, e);
    }

    void updateQuery(int n, int s, int e, int l, int r, Query q, int x) {
        propagate(n, s, e);
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            updateLazy(n, q, x);
            propagate(n, s, e);
            return;
        }

        int mid = (s + e) / 2;
        updateQuery(n << 1, s, mid, l, r, q, x);
        updateQuery(n << 1 | 1, mid + 1, e, l, r, q, x);
        tree[n] = tree[n << 1].merge(tree[n << 1 | 1]);
    }

    ll getQuery(int n, int s, int e, int l, int r, Query q) {
        propagate(n, s, e);
        if (e < l or r < s) {
            if (q == GET_MIN)
                return 1e9;
            else if (q == GET_MAX)
                return 1;
            else
                return 0;  // if (q == GET_SUM)
        }
        if (l <= s and e <= r) {
            if (q == GET_MIN)
                return tree[n].minimum;
            else if (q == GET_MAX)
                return tree[n].maximum;
            else
                return tree[n].sum;  // if (q == GET_SUM)
        }

        int mid = (s + e) / 2;
        ll lQuery = getQuery(n << 1, s, mid, l, r, q);
        ll rQuery = getQuery(n << 1 | 1, mid + 1, e, l, r, q);
        if (q == GET_MIN)
            return min(lQuery, rQuery);
        else if (q == GET_MAX)
            return max(lQuery, rQuery);
        else
            return lQuery + rQuery;
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
        int query;
        cin >> query;

        int l, r;
        cin >> l >> r;
        l--, r--;

        if (query <= 3) {
            int x;
            cin >> x;
            tree.updateQuery(1, 0, n - 1, l, r, Query(query), x);

            // cout << '\n';
            // for (int i = 0; i < n; i++) {
            //     cout << tree.getQuery(1, 0, n - 1, i, i, GET_SUM) << ' ';
            // }
            // cout << "\n\n";
        } else {
            // for (int i = 0; i < n; i++) {
            //     cout << tree.getQuery(1, 0, n - 1, i, i, GET_SUM) << ' ';
            // }
            // cout << tree.getQuery(1, 0, n-1, 0, n-1, GET_SUM);
            // cout << '\n';
            cout << tree.getQuery(1, 0, n - 1, l, r, Query(query)) << '\n';
        }
    }
}