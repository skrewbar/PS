#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll MOD = 1e9 + 7;

class SegmentTree {
   public:
    SegmentTree(int size) : size(size), t(size << 1) {}

    ll getRangeSum(int l, int r) {
        ll ret = 0;
        for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = (ret + t[l++]) % MOD;
            if (~r & 1)
                ret = (ret + t[r--]) % MOD;
        }
        return ret;
    }

    void add(int i, ll v) {
        i += size;
        t[i] = (t[i] + v) % MOD;
        for (; i > 1; i >>= 1)
            t[i >> 1] = (t[i] + t[i ^ 1]) % MOD;
    }

   private:
    int size;
    vector<ll> t;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<SegmentTree> trees(12, SegmentTree(n + 1));
    for (int i = 0; i < n; i++) {
        trees[1].add(arr[i], 1);
        for (int k = 2; k <= 11; k++) {
            trees[k].add(arr[i], trees[k - 1].getRangeSum(1, arr[i] - 1));
        }
    }
    cout << trees.back().getRangeSum(1, n) << '\n';
}