#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree() = default;
    SegmentTree(int n) : n(n), t(n << 1) {}

    SegmentTree &operator=(const SegmentTree &seg) {
        this->n = seg.n;
        this->t = seg.t;

        return *this;
    }

    void change(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }

    int getRangeSum(int l, int r) {
        int ret = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) ret += t[l++];
            if (~r & 1) ret += t[r--];
        }

        return ret;
    }
};

SegmentTree cnt[2];

void solve() {
    int n, q;
    cin >> n >> q;

    cnt[0] = cnt[1] = SegmentTree(n + 1);

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) cnt[0].change(i, 1);

    string str;
    cin >> str;
    str = '#' + str + '#';

    ll ans = 0;

    auto query = [&](int i) {
        if (s[i - 1] == s[i]) {
            ans += cnt[s[i]].getRangeSum(1, i - 1);
        } else {
            ans -= cnt[!s[i]].getRangeSum(1, i - 1);
        }

        if (s[i] == s[i + 1]) {
            ans += cnt[s[i]].getRangeSum(i + 1, n);
        } else {
            ans -= cnt[!s[i]].getRangeSum(i + 1, n);
        }

        if (s[i - 1] == s[i + 1]) {
            if (s[i - 1] == s[i]) {
                ans += (ll)(i - 1) * (n - i);
            } else {
                ans -= (ll)(i - 1) * (n - i);
            }
        }

        cnt[s[i]].change(i, 0);
        s[i] = !s[i];
        cnt[s[i]].change(i, 1);
    };

    for (int i = 1; i <= n; i++) {
        if (str[i] == '1') query(i);
    }

    print("{} ", ans);
    while (q--) {
        int i;
        cin >> i;

        query(i);
        print("{} ", ans);
    }
    println();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
