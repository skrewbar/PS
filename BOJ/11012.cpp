#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;
using ll = long long;

class SegmentTree {
   public:
    int n;
    vector<ll> tree;

    SegmentTree(int n) : n(n) {
        int height = ceil(log2(n)) + 1;
        tree = vector(1 << height, 0LL);
    }

    void addRange(int left, int right, ll value) {
        addRange(1, 0, n - 1, left, right, value);
    }

    ll get(int index) { return get(1, 0, n - 1, index); }

   private:
    void addRange(int node, int start, int end, int left, int right, ll value) {
        if (end < left or right < start)
            return;
        if (left <= start and end <= right) {
            tree[node] += value;
            return;
        }

        int mid = (start + end) >> 1;
        addRange(node << 1, start, mid, left, right, value);
        addRange(node << 1 | 1, mid + 1, end, left, right, value);
    }

    ll get(int node, int start, int end, int index) {
        if (start == end)
            return tree[node];

        int mid = (start + end) >> 1;
        if (index <= mid)
            return get(node << 1, start, mid, index) + tree[node];
        else
            return get(node << 1 | 1, mid + 1, end, index) + tree[node];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    SegmentTree segTree(100'100);
    vector<vector<int>> yCoords(100'100);
    while (n--) {
        int x, y;
        cin >> x >> y;
        yCoords[x].push_back(y);
    }

    vector<vector<pair<int, int>>> openQueries, closeQueries;
    openQueries = closeQueries = vector<vector<pair<int, int>>>(100'100);

    while (m--) {
        int l, r, b, t;
        cin >> l >> r >> b >> t;

        openQueries[l].emplace_back(b, t);
        closeQueries[r].emplace_back(b, t);
    }

    ll answer = 0;
    for (int x = 0; x <= 100'000; x++) {
        for (auto [l, r] : openQueries[x])
            segTree.addRange(l, r, 1);

        for (int y : yCoords[x])
            answer += segTree.get(y);

        for (auto [l, r] : closeQueries[x])
            segTree.addRange(l, r, -1);
    }

    print("{}\n", answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}