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

    int getRangeSum(int l, int r) {
        int sum = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) sum += t[l++];
            if (~r & 1) sum += t[r--];
        }

        return sum;
    }
};

int A[202020];
int lcnt[202020], rcnt[202020], lastIdx[202020];
vector<int> indices[202020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        indices[A[i]].push_back(i);
    }

    lcnt[0] = rcnt[0] = -1;
    for (int i = 1; i <= N; i++) {
        lcnt[i] = lcnt[lastIdx[A[i]]] + 1;
        lastIdx[A[i]] = i;
    }
    fill(lastIdx, lastIdx + M + 5, 0);
    for (int i = N; i >= 1; i--) {
        rcnt[i] = rcnt[lastIdx[A[i]]] + 1;
        lastIdx[A[i]] = i;
    }

    SegmentTree seg(M + 1);
    ll inv = 0;
    for (int i = 1; i <= N; i++) {
        inv += seg.getRangeSum(A[i] + 1, M - 1);
        seg.add(A[i], 1);
    }

    cout << inv << '\n';
    for (int v = M - 1; v > 0; v--) {
        for (int i : indices[v]) inv += i - 1 - lcnt[i] - (N - i - rcnt[i]);

        cout << inv << '\n';
    }

    return 0;
}
