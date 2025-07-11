#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int MOD = 1e9 + 7;

int power(long long base, int exp, int mod = MOD) {
    long long ret = 1;
    while (exp) {
        if (exp & 1)
            ret = (ret * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return ret;
}

struct Edge {
    int from, to;
};

struct DisjointSet {
    vector<int> parent;
    DisjointSet(int size) : parent(size) {
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int findParent(int v) {
        if (v != parent[v])
            parent[v] = findParent(parent[v]);
        return parent[v];
    }

    void unionParent(int u, int v) { parent[findParent(u)] = findParent(v); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto& [from, to] : edges)
        cin >> from >> to;

    int answer = 0;
    DisjointSet djs(n);
    for (int i = m - 1; i >= 0; i--) {
        auto [from, to] = edges[i];

        int startRoot = djs.findParent(0), endRoot = djs.findParent(n - 1),
            fromRoot = djs.findParent(from), toRoot = djs.findParent(to);

        if ((startRoot == fromRoot and endRoot == toRoot) or
            (startRoot == toRoot and endRoot == fromRoot))  // 컷
            answer = (answer + power(3, i)) % MOD;
        else
            djs.unionParent(from, to);
    }

    print("{}", answer);

    return 0;
}