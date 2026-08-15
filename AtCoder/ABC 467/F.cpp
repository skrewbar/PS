#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) v.begin(), v.end()
#define rank_desc(v, x) lower_bound(all(v), x, greater<>()) - v.begin()

vector<ll> compB;
vector<int> cnt;

struct SegmentTree {
    struct Node {
        ll sum, time;
    };
    static Node merge(const Node &l, const Node &r) {
        Node ret;

        ret.sum = l.sum + r.sum;
        ret.time = max(l.time, l.sum + r.time);

        return ret;
    }

    int n;
    vector<Node> t;

    SegmentTree(int _n) : n(1 << (32 - __builtin_clz(_n - 1))), t(n << 1) {}

    void change(int i, ll v) {
        t[i + n].time = ((t[i + n].sum = v) ? v + compB[i] : 0);
        i += n;

        for (i >>= 1; i >= 1; i >>= 1) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N + 1), B(N + 1);
    compB.reserve(N + Q);  // compressed B
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) {
        cin >> B[i];
        compB.push_back(B[i]);
    }

    vector<tuple<int, int, ll>> queries(Q);
    for (auto &[t, i, x] : queries) {
        cin >> t >> i >> x;
        if (t == 2) compB.push_back(x);
    }
    sort(all(compB), greater<>());
    cnt.resize(compB.size());

    auto getRank = [&](ll b) {
        int rank = rank_desc(compB, b);
        return rank + cnt[rank]++;
    };

    vector<int> Brank(N + 1);

    SegmentTree seg(compB.size());
    for (int i = 1; i <= N; i++) seg.change(Brank[i] = getRank(B[i]), A[i]);
    cerr << seg.t[1].time;

    for (auto [t, i, x] : queries) {
        if (t == 1) A[i] = x;
        else {
            seg.change(Brank[i], 0);
            B[i] = x;
            Brank[i] = getRank(B[i]);
        }

        seg.change(Brank[i], A[i]);
        cout << seg.t[1].time << '\n';
    }

    return 0;
}
