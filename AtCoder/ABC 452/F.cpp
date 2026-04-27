#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int n) : n(n), t(n << 1) {}

    void change(int i, int v) {
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

int P[505050];

ll N, K;

ll getLessOrEqualCnt(ll k) {
    ll ret = 0;
    ll inv = 0;
    int lo = 1, hi = 1;
    SegmentTree seg(N + 1);

    while (hi <= N) {
        inv += seg.getRangeSum(P[hi], N);
        seg.change(P[hi], 1);

        while (lo < hi and inv > k) {
            seg.change(P[lo], 0);
            inv -= seg.getRangeSum(0, P[lo]);
            lo++;
        }

        if (inv <= k)
            ret += hi - lo + 1;

        hi++;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> P[i];
    cout << getLessOrEqualCnt(K) - getLessOrEqualCnt(K - 1);

    return 0;
}