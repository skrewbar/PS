#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

struct SegmentTree {
    struct Node {
        ll sum, maxEnd;
    };
    Node merge(Node& left, Node& right) {
        Node ret;

        ret.sum = left.sum + right.sum;
        ret.maxEnd = max(left.maxEnd + right.sum, right.maxEnd);

        return ret;
    }

    vector<Node> t;

    SegmentTree(int n) : t(1 << (int)(ceil(log2(n)) + 1)) { init(1, 1, n); }
    void init(int node, int s, int e) {
        if (s == e) {
            t[node] = Node(0, s);
            return;
        }

        int m = (s + e) / 2;
        init(node << 1, s, m);
        init(node << 1 | 1, m + 1, e);
        t[node] = merge(t[node << 1], t[node << 1 | 1]);
    }

    void change(int node, int s, int e, int i, int v) {
        if (s == e) {
            t[node] = Node(v, s + v);
            return;
        }

        int m = (s + e) / 2;
        if (i <= m)
            change(node << 1, s, m, i, v);
        else
            change(node << 1 | 1, m + 1, e, i, v);

        t[node] = merge(t[node << 1], t[node << 1 | 1]);
    }

    ll query(int node, int s, int e, int i) {
        ll ret = 0;

        while (s < e) {
            int m = (s + e) / 2;

            if (i <= m) {
                node = node << 1;
                e = m;
                continue;
            }

            ret = max(t[node << 1].maxEnd, ret + t[node << 1].sum);
            node = node << 1 | 1;
            s = m + 1;
        }
        ret = max(t[node].maxEnd, ret + t[node].sum);

        return ret;
    }
};

const int MAX_TIME = 1e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SegmentTree tree(MAX_TIME);

    int q;
    cin >> q;

    vector<int> joinTime(q + 1);

    for (int k = 1; k <= q; k++) {
        char type;
        cin >> type;

        if (type == '+') {
            int t, d;
            cin >> t >> d;

            joinTime[k] = t;
            tree.change(1, 1, MAX_TIME, t, d);
        } else if (type == '-') {
            int i;
            cin >> i;

            tree.change(1, 1, MAX_TIME, joinTime[i], 0);
        } else {
            int t;
            cin >> t;

            println("{}", max(tree.query(1, 1, MAX_TIME, t) - t, 0LL));
        }
    }

    return 0;
}