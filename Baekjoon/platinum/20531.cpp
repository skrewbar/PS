#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

template <size_t n>
struct DisjointSet {
    int parent[n];

    DisjointSet() {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findParent(int v) {
        if (v != parent[v])
            parent[v] = findParent(parent[v]);
        return parent[v];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);
        parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};
DisjointSet<5050> disjointSet;

long long dp[5050][5050];
long long MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        dp[i][1] = 1;
        for (int j = 2; j <= N; j++) {
            dp[i][j] = dp[i - 1][j] * j + dp[i - 1][j - 1];
            dp[i][j] %= MOD;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 2; j <= N; j++) {
            dp[i][j] += dp[i][j - 1];
            dp[i][j] %= MOD;
        }
    }

    int components = N;
    while (M--) {
        int x, y;
        cin >> x >> y;

        if (not disjointSet.isConnected(x, y))
            components--;
        disjointSet.unionParent(x, y);

        cout << dp[components][components] << '\n';
    }

    return 0;
}