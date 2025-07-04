#include <bits/stdc++.h>
#include <algorithm>

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

    int getSuffixSum(int i) { return getPrefixSum(n) - getPrefixSum(i - 1); }
};
FenwickTree<100'100> cntTree;

int rootN;
struct Query {
    int l, r, index;

    bool operator<(const Query& q) const {
        if (l / rootN != q.l / rootN)
            return l / rootN < q.l / rootN;
        return r < q.r;
    }
} queries[100'100];

int arr[100'100];
ll answer[100'100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    rootN = sqrt(n);

    vector<int> values = {-1};
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        values.push_back(arr[i]);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for (int i = 1; i <= n; i++)
        arr[i] =
            lower_bound(values.begin(), values.end(), arr[i]) - values.begin();
    ;

    for (int i = 1; i <= m; i++) {
        auto& [l, r, index] = queries[i];
        cin >> l >> r;
        index = i;
    }
    sort(queries + 1, queries + m + 1);

    int l, r;
    l = r = (queries[1].l + queries[1].r) / 2;
    cntTree.add(arr[l], 1);
    ll pairCnt = 0;

    for (int i = 1; i <= m; i++) {
        const Query& q = queries[i];

        while (q.l < l) {
            cntTree.add(arr[--l], 1);
            pairCnt += cntTree.getPrefixSum(arr[l] - 1);
        }
        while (r < q.r) {
            cntTree.add(arr[++r], 1);
            pairCnt += cntTree.getSuffixSum(arr[r] + 1);
        }

        while (l < q.l) {
            cntTree.add(arr[l], -1);
            pairCnt -= cntTree.getPrefixSum(arr[l++] - 1);
        }
        while (q.r < r) {
            cntTree.add(arr[r], -1);
            pairCnt -= cntTree.getSuffixSum(arr[r--] + 1);
        }

        answer[q.index] = pairCnt;
    }

    for (int i = 1; i <= m; i++)
        print("{}\n", answer[i]);
    return 0;
}