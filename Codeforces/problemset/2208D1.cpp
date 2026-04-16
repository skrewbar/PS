#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) { iota(all(parent), 0); }

    int findParent(int x) {
        if (x != parent[x])
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);

        if (u != v)
            parent[v] = u;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

int n;
bool reachable[555][555];
vector<pair<int, int>> edges;

void solve() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        string line;
        cin >> line;

        for (int j = 1; j <= n; j++)
            reachable[i][j] = (line[j - 1] == '1');
    }

    for (int i = 1; i <= n; i++) {
        if (not reachable[i][i]) {
            println("No");
            return;
        }
    }

    edges.clear();
    DisjointSet ds(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == i)
                continue;

            if (reachable[i][j] and reachable[j][i]) {
                println("No");
                return;
            }

            bool adjacent = true;
            for (int k = 1; k <= n; k++) {
                if (k == i or k == j)
                    continue;

                if (not reachable[i][k] or not reachable[k][j])
                    continue;

                if (reachable[i][j]) {
                    adjacent = false;
                    break;
                }
                println("No");
                return;
            }

            if (reachable[i][j] and adjacent) {
                if (ds.isConnected(i, j)) {
                    println("No");
                    return;
                }
                ds.unionParent(i, j);
                edges.emplace_back(i, j);
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (not ds.isConnected(1, i)) {
            println("No");
            return;
        }
    }

    println("Yes");
    for (auto& [x, y] : edges)
        println("{} {}", x, y);
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