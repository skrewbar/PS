#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
class SegmentTree {
   public:
    SegmentTree(size_t size) : n(size), t(size << 1) {}

    struct Proxy {
        SegmentTree& tree;
        size_t i;

        Proxy& operator++(int) {
            tree.add(i);
            return *this;
        }
        operator T() { return tree.t[i + tree.n]; }
    };
    Proxy operator[](size_t i) { return Proxy(*this, i); }

    T getRangeSum(size_t l, size_t r) {
        T ret = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret += t[l++];
            if (~r & 1)
                ret += t[r--];
        }
        return ret;
    }

   private:
    size_t n;
    vector<T> t;

    void add(size_t i) {
        for (t[i += n]++; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> prices(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> prices[i];

    ll p;
    cin >> p;
    vector<ll> values = {0};
    for (int i = 1; i <= n; i++) {
        prices[i] += prices[i - 1];
        values.push_back(prices[i] - p * i);
    }
    ranges::sort(values);
    values.erase(ranges::unique(values).begin(), values.end());

    SegmentTree<ll> tree(values.size());
    ll answer = 0;
    for (int i = 1; i <= n; i++) {
        size_t update =
            ranges::lower_bound(values, prices[i - 1] - p * (i - 1)) -
            values.begin();
        tree[update]++;
        size_t bound =
            ranges::lower_bound(values, prices[i] - p * i) - values.begin();
        answer += tree.getRangeSum(0, bound);
    }
    cout << answer;
}