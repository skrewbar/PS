#include <bits/stdc++.h>
using namespace std;
using ll = long long;


class SegmentTree {
private:
    int size;
    vector<ll> tree;

    void set(int index, ll value) {
        index += size;
        for (tree[index] = value; index > 1; index >>= 1) {
            tree[index >> 1] = max(tree[index], tree[index^1]);
        }
    }

    ll getRangeMax(int l, int r) {
        ll ret = -10e9;
        for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) ret = max(tree[l++], ret);
            if (~r & 1) ret = max(tree[r--], ret);
        }
        return ret;
    }
public:
    SegmentTree(const vector<ll> &v): size(v.size()) {
        tree = vector<ll>(size * 2);

        for (int i = 0; i < size; i++) tree[size+i] = v[i];
        for (int i = size-1; i > 0; i--) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }

    /* tree[i] = value 방식으로 세그트리 업데이트 */
    struct Proxy {
        SegmentTree &tree;
        int index;

        Proxy &operator=(ll value) {
            tree.set(index, value);
            return *this;
        }
    };
    Proxy operator[](int i) {
        return Proxy{*this, i};
    }

    /* tree(start, end) 방식으로 구간 쿼리 */
    ll operator()(int start, int end) {
        return getRangeMax(start, end);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    cin >> n >> d;
    vector<long long> stones(n);
    for (int i = 0; i < n; i++) cin >> stones[i];

    SegmentTree dp(stones);
    for (int i = 1; i < n; i++) {
        dp[i] = max(dp(max(i - d, 0), i-1), 0LL) + stones[i];
    }
    cout << dp(0, n-1);
}