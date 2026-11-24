#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll power(ll base, ll exp, ll mod) {
    ll ret = 1;

    while (exp) {
        if (exp & 1)
            ret = ret * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }

    return ret;
}

ll N, M;
vector<int> adj[303030];
ll dp[303030][2];

void setRoot(int root, int parent = -1) {
    // remove parent from adjacency list
    for (int i = 0; i < adj[root].size(); i++) {
        if (adj[root][i] == parent) {
            swap(adj[root][i], adj[root].back());
            adj[root].pop_back();
            break;
        }
    }

    // set subtree's root
    for (int child : adj[root])
        setRoot(child, root);
}

void dfs(int node) {
    dp[node][0] = 1;
    for (int child : adj[node]) {
        dfs(child);

        dp[node][0] *= (dp[child][0] + dp[child][1]) % M;
        dp[node][0] %= M;
    }

    if (adj[node].empty())
        return;

    // prefixMul[i] represents the multiple of range [0, i)
    vector<ll> prefixMul(adj[node].size());
    prefixMul[0] = 1;
    for (int i = 0; i < adj[node].size() - 1; i++) {
        prefixMul[i + 1] = prefixMul[i] *
                           ((dp[adj[node][i]][0] + dp[adj[node][i]][1]) % M) %
                           M;
    }

    // suffixMul[i] represents the multiple of range (i, end]
    vector<ll> suffixMul(adj[node].size());
    suffixMul[adj[node].size() - 1] = 1;
    for (int i = adj[node].size() - 1; i > 0; i--) {
        suffixMul[i - 1] = suffixMul[i] *
                           ((dp[adj[node][i]][0] + dp[adj[node][i]][1]) % M) %
                           M;
    }

    for (int i = 0; i < adj[node].size(); i++) {
        dp[node][1] +=
            prefixMul[i] * dp[adj[node][i]][0] % M * suffixMul[i] % M;
        dp[node][1] %= M;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    setRoot(1);
    dfs(1);

    cout << ((power(2, N, M) - 2 * (dp[1][0] + dp[1][1])) % M + M) % M;

    return 0;
}