#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

class SegmentTree {
   private:
    int n;
    vector<ll> t;

    void add(int node, int s, int e, int l, int r, ll v) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            t[node] += v;
            return;
        }

        int m = (s + e) / 2;
        add(node << 1, s, m, l, r, v);
        add(node << 1 | 1, m + 1, e, l, r, v);
    }

    ll get(int node, int s, int e, int i) {
        if (i < s or e < i)
            return 0;
        if (s == e)
            return t[node];

        int m = (s + e) / 2;
        ll lsum = get(node << 1, s, m, i);
        ll rsum = get(node << 1 | 1, m + 1, e, i);
        return lsum + rsum + t[node];
    }

   public:
    SegmentTree(int _n) : n(_n) {
        t = vector<ll>(1 << ((int)ceil(log2(n)) + 1));
    }

    void add(int l, int r, ll v) {
        if (l > r)
            return;

        add(1, 0, n - 1, l, r, v);
    }
    ll get(int i) { return get(1, 0, n - 1, i); }
};

vector<int> childs[505050];
int salary[505050], in[505050], out[505050];

void eulerTour(int at) {
    static int counter = 0;

    in[at] = counter++;
    for (int nxt : childs[at])
        eulerTour(nxt);
    out[at] = counter - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    cin >> salary[1];
    for (int i = 2; i <= N; i++) {
        int parent;
        cin >> salary[i] >> parent;

        childs[parent].push_back(i);
    }
    eulerTour(1);

    SegmentTree segTree(N);

    for (int i = 1; i <= N; i++)
        segTree.add(in[i], in[i], salary[i]);

    while (M--) {
        char type;
        cin >> type;

        if (type == 'p') {
            int a;
            ll x;
            cin >> a >> x;

            segTree.add(in[a] + 1, out[a], x);
        } else {
            int a;
            cin >> a;

            println("{}", segTree.get(in[a]));
        }
    }

    return 0;
}