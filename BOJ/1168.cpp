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

    SegmentTree(int _n) : n(_n) {
        int height = ceil(log2(n)) + 1;
        t.resize(1 << height);
    }

    void modify(int i, int v) { modify(1, 0, n - 1, i, v); }
    int kth(int k) { return kth(1, 0, n - 1, k); }

   private:
    void modify(int node, int s, int e, int i, int v) {
        if (s == e) {
            t[node] = v;
            return;
        }

        int m = (s + e) / 2;
        if (i <= m)
            modify(node << 1, s, m, i, v);
        else
            modify(node << 1 | 1, m + 1, e, i, v);

        t[node] = t[node << 1] + t[node << 1 | 1];
    }
    int kth(int node, int s, int e, int k) {
        if (s == e)
            return s;

        int m = (s + e) / 2;
        if (t[node << 1] > k)
            return kth(node << 1, s, m, k);
        else
            return kth(node << 1 | 1, m + 1, e, k - t[node << 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    SegmentTree segTree(N + 1);
    for (int i = 1; i <= N; i++)
        segTree.modify(i, 1);

    cout << '<';
    int k = 0;
    for (int i = 0; i < N - 1; i++) {
        k = (k - 1 + K) % (N - i);

        int kth = segTree.kth(k);
        cout << kth << ", ";
        segTree.modify(kth, 0);
    }
    cout << segTree.kth(0) << '>';

    return 0;
}