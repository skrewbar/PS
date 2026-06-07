#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int n) : n(n), t(n << 1) {}

    void add(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }

    int rangeSum(int l, int r) {
        int sum = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) sum += t[l++];
            if (~r & 1) sum += t[r--];
        }

        return sum;
    }
};

int prv[2][303030];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    fill(prv[0], prv[0] + N + 1, -1);

    ll ans = 0;
    vector<SegmentTree> t(2, SegmentTree(Q + 1));

    for (int i = 1; i <= Q; i++) {
        int type, x;
        cin >> type >> x;

        type--;

        if (prv[type][x] == -1) {
            ans += N;
        } else {
            int cnt = t[type ^ 1].rangeSum(prv[type][x], Q);
            ans += (type ? -cnt : cnt);
            t[type].add(prv[type][x], -1);
        }

        prv[type][x] = i;
        t[type].add(i, 1);

        cout << ans << '\n';
    }

    return 0;
}
