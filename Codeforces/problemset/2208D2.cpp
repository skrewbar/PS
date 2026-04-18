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

bool reachable[8080][8080];
int reachableCntFrom[8080];
vector<pair<int, int>> edges;

void solve() {
    int n;
    cin >> n;

    fill(reachableCntFrom + 1, reachableCntFrom + n + 1, 0);

    for (int i = 1; i <= n; i++) {
        string line;
        cin >> line;

        for (int j = 1; j <= n; j++) {
            reachable[i][j] = (line[j - 1] == '1');
            if (reachable[i][j])
                reachableCntFrom[i]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (not reachable[i][i]) {
            println("No");
            return;
        }
    }

    edges.clear();
    for (int i = 1; i <= n; i++) {
        bitset<8080> isCandidate;
        for (int j = 1; j <= n; j++)
            isCandidate[j] = reachable[i][j];
        isCandidate[i] = false;

        while (isCandidate.any()) {
            int maximum = 0;

            for (int j = 1; j <= n; j++) {
                if (not isCandidate[j])
                    continue;

                if (reachableCntFrom[j] > reachableCntFrom[maximum])
                    maximum = j;
            }

            edges.emplace_back(i, maximum);
            if (edges.size() >= n) {
                println("No");
                return;
            }

            for (int j = 1; j <= n; j++) {
                if (not reachable[maximum][j])
                    continue;

                if (not reachable[i][j]) {
                    println("No");
                    return;
                }

                isCandidate[j] = false;
            }
        }
    }

    if (edges.size() != n - 1) {
        println("No");
        return;
    }

    DisjointSet ds(n + 1);
    for (auto [u, v] : edges) {
        if (ds.isConnected(u, v)) {
            println("No");
            return;
        }
        ds.unionParent(u, v);
    }
    for (int i = 2; i <= n; i++) {
        if (not ds.isConnected(1, i)) {
            println("No");
            return;
        }
    }

    println("Yes");
    for (auto& [u, v] : edges)
        println("{} {}", u, v);
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