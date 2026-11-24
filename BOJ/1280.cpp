#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<ll> t;

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void add(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    ll getRangeSum(int l, int r) {
        ll ret = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret += t[l++];
            if (~r & 1)
                ret += t[r--];
        }

        return ret;
    }
} sumTree(202020), cntTree(202020);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int pos;
    cin >> pos;
    sumTree.add(pos, pos);
    cntTree.add(pos, 1);

    N--;

    ll ans = 1;
    while (N--) {
        cin >> pos;

        ll left =
            (pos * cntTree.getRangeSum(0, pos) - sumTree.getRangeSum(0, pos)) % MOD;
        ll right = (sumTree.getRangeSum(pos, sumTree.n - 1) -
                   pos * cntTree.getRangeSum(pos, cntTree.n - 1)) % MOD;

        ans = ans * ((left + right) % MOD) % MOD;

        sumTree.add(pos, pos);
        cntTree.add(pos, 1);
    }

    cout << (ans + MOD) % MOD;

    return 0;
}