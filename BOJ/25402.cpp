#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

struct DisjointSet {
    vector<int> parent;
    vector<int> count;

    DisjointSet(size_t size) : parent(size), count(size) {}

    int findRoot(int v) {
        if (parent[v] == v)
            return v;
        return parent[v] = findRoot(parent[v]);
    }

    void unionRoot(int u, int v) {
        u = findRoot(u), v = findRoot(v);
        count[u] += count[v];
        parent[v] = u;
    }
};

vector<vector<int>> adj;
vector<int> parent;

void buildParent(int v) {
    for (int child : adj[v]) {
        if (parent[child] != -1)
            continue;
        parent[child] = v;
        buildParent(child);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    adj = vector(n + 1, vector<int>());
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    parent = vector(n + 1, -1);
    parent[1] = 0;
    buildParent(1);

    vector<int> s(n + 1);
    DisjointSet disjointSet(n + 1);
    vector<int> lastQuery(n + 1);

    int q;
    cin >> q;
    for (int query = 1; query <= q; query++) {
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++) {
            cin >> s[i];
            lastQuery[s[i]] = query;
            disjointSet.parent[s[i]] = s[i];
            disjointSet.count[s[i]] = 1;
        }

        for (int i = 1; i <= k; i++) {
            if (lastQuery[parent[s[i]]] == query) {
                disjointSet.unionRoot(parent[s[i]], s[i]);
            }
        }

        ll answer = 0;
        for (int i = 1; i <= k; i++) {
            if (disjointSet.findRoot(s[i]) != s[i])
                continue;
            ll count = disjointSet.count[s[i]];
            answer += count * (count - 1) / 2;
        }

        cout << answer << '\n';
    }
}