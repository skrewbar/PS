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

constexpr ll BASE1 = 7;
constexpr ll BASE2 = 101;
constexpr ll MOD = 1e9 + 7;

struct Edge {
    int to;
    char flower;
};

vector<vector<Edge>> adj;
string p;
ll hashP1, hashP2;
vector<bool> visited;

int getManYoungRhoCount(int u, ll hash1, ll hash2, vector<char>& road) {
    int ret = 0;
    if (hash1 == hashP1 and hash2 == hashP2)
        ret++;

    if (road.size() >= p.size()) {
        hash1 -= *(road.end() - p.size()) * power(BASE1, p.size() - 1, MOD);
        hash2 -= *(road.end() - p.size()) * power(BASE2, p.size() - 1, MOD);
        hash1 = (hash1 % MOD + MOD) % MOD;
        hash2 = (hash2 % MOD + MOD) % MOD;
    }
    hash1 = (hash1 * BASE1) % MOD;
    hash2 = (hash2 * BASE2) % MOD;

    for (auto [to, flower] : adj[u]) {
        if (visited[to])
            continue;
        visited[to] = true;

        road.push_back(flower);
        ret += getManYoungRhoCount(to, hash1 + flower, hash2 + flower, road);
        road.pop_back();
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj = vector<vector<Edge>>(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        char c;
        cin >> c;

        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    cin >> p;

    for (int i = 0; i < (int)p.size(); i++) {
        hashP1 += p[i] * power(BASE1, p.size() - (i + 1), MOD);
        hashP2 += p[i] * power(BASE2, p.size() - (i + 1), MOD);
        hashP1 %= MOD;
        hashP2 %= MOD;
    }

    visited = vector(n, false);
    visited[0] = true;
    vector<char> road;
    cout << getManYoungRhoCount(0, 0, 0, road);

    return 0;
}