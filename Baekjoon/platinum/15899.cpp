#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

class MergeSortTree {
   private:
    vector<vector<int>> t;
    int n;

    int getLessOrEqualCount(int node, int s, int e, int l, int r, int v) {
        if (e < l or r < s)
            return 0;
        if (l <= s and e <= r)
            return ranges::upper_bound(t[node], v) - t[node].begin();

        int m = (s + e) / 2;
        int leftCount = getLessOrEqualCount(node << 1, s, m, l, r, v);
        int rightCount = getLessOrEqualCount(node << 1 | 1, m + 1, e, l, r, v);

        return leftCount + rightCount;
    }

   public:
    MergeSortTree(const vector<int>& arr) : n(arr.size()) {
        t = vector<vector<int>>(1 << ((int)ceil(log2(n)) + 1));

        function<void(int, int, int)> init = [&](int node, int s, int e) {
            if (s == e) {
                t[node] = {arr[s]};
                return;
            }

            int m = (s + e) / 2;
            init(node << 1, s, m);
            init(node << 1 | 1, m + 1, e);

            const vector<int>&left = t[node << 1], &right = t[node << 1 | 1];
            t[node] = vector<int>(left.size() + right.size());
            merge(left.begin(), left.end(), right.begin(), right.end(),
                  t[node].begin());
        };

        init(1, 0, n - 1);
    }

    int getLessOrEqualCount(const pair<int, int>& range, int value) {
        return getLessOrEqualCount(1, 0, n - 1, range.first, range.second,
                                   value);
    }
};

vector<vector<int>> adj;
vector<int> in, out;

void eulerTour(int at, int parent) {
    static int visitedCount = 0;

    in[at] = visitedCount++;

    for (int nxt : adj[at]) {
        if (nxt == parent)
            continue;

        eulerTour(nxt, at);
    }

    out[at] = visitedCount - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, C;
    cin >> N >> M >> C;

    vector<int> color(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> color[i];

    adj.resize(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    in.resize(N + 1);
    out.resize(N + 1);
    eulerTour(1, -1);

    vector<int> tourColor(N);
    for (int i = 1; i <= N; i++)
        tourColor[in[i]] = color[i];
    MergeSortTree mst(tourColor);

    int ans = 0;
    while (M--) {
        int v, c;
        cin >> v >> c;

        ans += mst.getLessOrEqualCount({in[v], out[v]}, c);
        ans %= MOD;
    }

    println("{}", ans);

    return 0;
}