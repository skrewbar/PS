#include <bits/stdc++.h>
#include <ios>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct SegmentTree {
    vector<int> t;

    SegmentTree(int n) {
        int height = (int)ceil(log2(n)) + 1;
        t.assign(1 << height, 0);
    }

    void modify(int node, int start, int end, int index, int value) {
        if (start == end) {
            t[node] = value;
            return;
        }

        int mid = (start + end) >> 1;
        if (index <= mid)
            modify(node << 1, start, mid, index, value);
        else
            modify(node << 1 | 1, mid + 1, end, index, value);

        t[node] = t[node << 1] + t[node << 1 | 1];
    }

    int getRangeSum(int node, int start, int end, int left, int right) {
        if (right < left or right < start)
            return 0;
        if (left <= start and end <= right)
            return t[node];

        int mid = (start + end) >> 1;
        int lsum = getRangeSum(node << 1, start, mid, left, right);
        int rsum = getRangeSum(node << 1 | 1, mid + 1, end, left, right);
        return lsum + rsum;
    }

    int popNthStone(int node, int start, int end, int n) {
        if (start == end) {
            t[node] = 0;
            return start;
        }

        int mid = (start + end) >> 1;
        int ret;

        if (n <= t[node << 1])
            ret = popNthStone(node << 1, start, mid, n);
        else
            ret = popNthStone(node << 1 | 1, mid + 1, end, n - t[node << 1]);

        t[node] = t[node << 1] + t[node << 1 | 1];
        return ret;
    }
};

void solve(int n, int k, int m) {
    SegmentTree segTree(n + 1);
    for (int i = 1; i <= n; i++)
        segTree.modify(1, 1, n, i, 1);

    int removed = segTree.popNthStone(1, 1, n, m);

    while (segTree.t[1])
        removed = segTree.popNthStone(
            1, 1, n,
            (segTree.getRangeSum(1, 1, n, 1, removed) + k - 1) % segTree.t[1] +
                1);

    cout << removed << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    while (true) {
        cin >> n >> m >> k;
        if (n == 0)
            break;
        solve(n, m, k);
    }

    return 0;
}