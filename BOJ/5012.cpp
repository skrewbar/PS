#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<ll> t;

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void add(int i, ll v) {
        for (t[i += n] += v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    ll getRangeSum(int l, int r) {
        ll sum = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                sum += t[l++];
            if (~r & 1)
                sum += t[r--];
        }

        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<SegmentTree> inversionCount(3, SegmentTree(n));
    for (int i = 0; i < n; i++) {
        inversionCount[0].add(a[i], 1);
        for (int j = 1; j < 3; j++)
            inversionCount[j].add(
                a[i], inversionCount[j - 1].getRangeSum(a[i] + 1, n - 1));
    }

    println("{}", inversionCount.back().getRangeSum(0, n - 1));

    return 0;
}