#include <algorithm>
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct SegmentTree {
    int n;
    vector<pair<int, int>> t;

    pair<int, int> merge(const pair<int, int> p1, const pair<int, int> p2) {
        pair<int, int> ret = minmax(p1.second, p2.second);
        ret.first = max(ret.first, max(p1.first, p2.first));
        return ret;
    }

    SegmentTree(const vector<int>& arr): n(arr.size()), t(arr.size() << 1) {
        for (int i = 0; i < n; i++)
            t[i + n] = pair(1, arr[i]);
        
        for (int i = n - 1; i > 0; i--)
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void change(int i, int v) {
        for (t[i += n].second = v; i > 1; i >>= 1)
            t[i >> 1] = merge(t[i], t[i ^ 1]);
    }

    pair<int, int> getRangeTwoMax(int l, int r) {
        pair<int, int> ret(0, 0);

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = merge(ret, t[l++]);
            if (~r & 1)
                ret = merge(ret, t[r--]);
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    SegmentTree tree(arr);

    int m;
    cin >> m;
    while (m--) {
        int q;
        cin >> q;

        if (q == 1) {
            int i, v;
            cin >> i >> v;
            i--;
            tree.change(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto [m1, m2] = tree.getRangeTwoMax(l, r);
            print("{}\n", m1 + m2);
        }
    }

    return 0;
}