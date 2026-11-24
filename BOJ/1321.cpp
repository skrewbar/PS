#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void add(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    int getRangeSum(int l, int r) {
        int ret = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret += t[l++];
            if (~r & 1)
                ret += t[r--];
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    SegmentTree segTree(N + 1);
    for (int i = 1; i <= N; i++) {
        int v;
        cin >> v;
        segTree.add(i, v);
    }

    int M;
    cin >> M;
    while (M--) {
        int q, i;
        cin >> q >> i;

        if (q == 1) {
            int a;
            cin >> a;

            segTree.add(i, a);
        } else {
            int lo = 1, hi = N;

            while (lo < hi) {
                int m = (lo + hi) / 2;

                if (segTree.getRangeSum(1, m) < i)
                    lo = m + 1;
                else
                    hi = m;
            }

            cout << lo << '\n';
        }
    }

    return 0;
}