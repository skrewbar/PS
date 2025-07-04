#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

template <int n>
struct FenwickTree {
    int t[n + 1] = {};

    void add(int i, int v) {
        while (i < n) {
            t[i] += v;
            i += i & -i;
        }
    }

    int getPrefixSum(int i) {
        int ret = 0;
        while (i > 0) {
            ret += t[i];
            i -= i & -i;
        }
        return ret;
    }

    int getRangeSum(int l, int r) {
        l = max(l, 1);
        r = min(r, n);
        return getPrefixSum(r) - getPrefixSum(l - 1);
    }
};

FenwickTree<100'100> cntTree;

int rootN;
int arr[100'100];
ll answer[100'100];

struct Query {
    int l, r, index;

    bool operator<(const Query& q) const {
        if (l / rootN != q.l / rootN)
            return l / rootN < q.l / rootN;
        return r < q.r;
    }
} queries[100'100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    rootN = sqrt(n);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        auto& [l, r, index] = queries[i];
        cin >> l >> r;
        l--, r--;
        index = i;
    }
    sort(queries, queries + m);

    int l, r;
    l = r = (queries[0].l + queries[0].r) / 2;
    cntTree.add(arr[l], 1);
    ll pairCnt = 0;
    for (int i = 0; i < m; i++) {
        const Query& q = queries[i];
        while (q.l < l) {
            l--;
            pairCnt += cntTree.getRangeSum(arr[l] - k, arr[l] + k);
            cntTree.add(arr[l], 1);
        }
        while (r < q.r) {
            r++;
            pairCnt += cntTree.getRangeSum(arr[r] - k, arr[r] + k);
            cntTree.add(arr[r], 1);
        }

        while (l < q.l) {
            cntTree.add(arr[l], -1);
            pairCnt -= cntTree.getRangeSum(arr[l] - k, arr[l] + k);
            l++;
        }
        while (q.r < r) {
            cntTree.add(arr[r], -1);
            pairCnt -= cntTree.getRangeSum(arr[r] - k, arr[r] + k);
            r--;
        }

        answer[q.index] = pairCnt;
    }

    for (int i = 0; i < m; i++)
        print("{}\n", answer[i]);

    return 0;
}