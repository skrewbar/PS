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

    SegmentTree(int _n): n(_n), t(n << 1) {}

    void modify(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    int getRangeSum(int l, int r) {
        int sum = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                sum += t[l++];
            if (~r & 1)
                sum += t[r--];
        }

        return sum;
    }
};

void solve() {
    int n;
    cin >> n;

    SegmentTree seg(n);

    vector<int> perm1(n), pos(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> perm1[i];
        pos[perm1[i]] = i;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        ans += seg.getRangeSum(pos[x], n - 1);
        seg.modify(pos[x], 1);
    }

    println("{}", ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}