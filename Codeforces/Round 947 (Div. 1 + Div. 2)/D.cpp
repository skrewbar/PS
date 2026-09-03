#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n;
    cin >> n;

    int a, b;
    cin >> a >> b;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> dist(n + 1), parent(n + 1);
    auto calcDist = [&](auto &&self, int v) -> void {
        for (int c : adj[v]) {
            if (c == parent[v]) continue;
            dist[c] = dist[v] + 1;
            parent[c] = v;
            self(self, c);
        }
    };
    parent[a] = -1;
    calcDist(calcDist, a);

    int rd = (dist[b] + 1) / 2;
    int mid = b;
    while (dist[mid] > dist[b] / 2) mid = parent[mid];

    parent[mid] = -1;
    dist[mid] = 0;
    calcDist(calcDist, mid);

    int maxD = *max_element(all(dist));

    cout << rd + 2 * (n - 1) - maxD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
