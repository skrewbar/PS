#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

template <typename T, int n>
struct SegmentTree {
    T t[n << 1] = {};

    void add(int i, T x) {
        for (t[i += n] += x; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    T getRangeSum(int l, int r) {
        T ret = T();

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

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    while (m--) {
        int i, j;
        cin >> i >> j;

        adj[i].push_back(j);
    }

    SegmentTree<ll, 2020> tree;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j : adj[i])
            ans += tree.getRangeSum(j + 1, n);

        for (int j : adj[i])
            tree.add(j, 1);
    }

    print("{}", ans);
}