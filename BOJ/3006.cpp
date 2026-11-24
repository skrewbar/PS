#include <bits/stdc++.h>
#include <algorithm>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void modify(int i, int v) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    vector<int> sortedArr(arr);
    sort(sortedArr.begin(), sortedArr.end());

    vector<int> pos(N);
    for (int i = 0; i < N; i++) {
        int rank = ranges::lower_bound(sortedArr, arr[i]) - sortedArr.begin();
        pos[rank] = i;
    }

    SegmentTree segTree(N);
    for (int i = 0; i < N; i++)
        segTree.modify(i, 1);

    for (int i = 0; i < N; i++) {
        int cnt;
        if ((i + 1) % 2 == 1) {
            segTree.modify(pos[i / 2], 0);
            cnt = segTree.getRangeSum(0, pos[i / 2]);
        } else {
            segTree.modify(pos[N - 1 - i / 2], 0);
            cnt = segTree.getRangeSum(pos[N - 1 - i / 2], N - 1);
        }
        println("{}", cnt);
    }

    return 0;
}