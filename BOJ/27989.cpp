#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

template <typename T>
struct SegmentTree {
    size_t n;
    vector<T> t;

    SegmentTree(size_t n) : n(n), t(n << 1) {}

    void modify(int i, T v) {
        for (t[i += n] = v; i > 1; i >>= 1)
            t[i >> 1] = max(t[i], t[i ^ 1]);
    }

    T getRangeMax(int l, int r) {
        T ret = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = max(ret, t[l++]);
            if (~r & 1)
                ret = max(ret, t[r--]);
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    SegmentTree<ll> dpTree(N + 1);

    vector<pair<ll, int>> A;
    A.reserve(N);
    for (int i = 1; i <= N; i++) {
        ll A_i;
        cin >> A_i;
        A.emplace_back(A_i, i);
    }
    ranges::sort(A, [&](pair<ll, int> a, pair<ll, int> b) {
        if (a.first != b.first)
            return a.first < b.first;
        return a.second > b.second;
    });

    ll answer = 0;
    for (auto [A_i, i] : A) {
        ll lisSum = dpTree.getRangeMax(1, i) + A_i;
        dpTree.modify(i, lisSum);
        answer = max(answer, lisSum);
    }

    cout << answer << '\n';
    return 0;
}