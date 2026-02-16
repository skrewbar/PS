#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

constexpr int MOD = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void add(int i, int v) {
        i += n;
        t[i] = (t[i] + v) % MOD;
        for (; i > 1; i >>= 1)
            t[i >> 1] = (t[i] + t[i ^ 1]) % MOD;
    }

    int getRangeSum(int l, int r) {
        int sum = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                sum = (sum + t[l++]) % MOD;
            if (~r & 1)
                sum = (sum + t[r--]) % MOD;
        }

        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<SegmentTree> segTrees(K, SegmentTree(N + 1));

    for (int i = 0; i < N; i++) {
        segTrees[0].add(A[i], 1);

        for (int j = 1; j < K; j++)
            segTrees[j].add(A[i], segTrees[j - 1].getRangeSum(1, A[i] - 1));
    }

    println("{}", segTrees.back().getRangeSum(1, N));

    return 0;
}