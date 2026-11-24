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

    // n must be a power of 2
    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void add(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    int kth(int k) {
        int i = 1;

        while (i < n) {
            if (t[i << 1] >= k) {
                i = i << 1;
            } else {
                k -= t[i << 1];
                i = i << 1 | 1;
            }
        }

        return i - n;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    SegmentTree segTree(1 << 21);

    while (N--) {
        int T, X;
        cin >> T >> X;

        if (T == 1) {
            segTree.add(X, 1);
        } else {
            int kth = segTree.kth(X);
            cout << kth << '\n';
            segTree.add(kth, -1);
        }
    }

    return 0;
}