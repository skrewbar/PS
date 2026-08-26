#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> childs(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        childs[p].push_back(i);
    }

    vector<int> depth(n + 1);
    auto calcDepth = [&](auto &&self, int v) -> void {
        for (int c : childs[v]) {
            depth[c] = depth[v] + 1;
            self(self, c);
        }
    };
    calcDepth(calcDepth, 1);

    int m;
    cin >> m;

    vector<int> a(m + 1);
    for (int i = 1; i <= m; i++) cin >> a[i];

    sort(a.begin() + 1, a.end(),
         [&](int u, int v) { return depth[u] > depth[v]; });

    cout << m - 1 << ' ';
    for (int i = 1; i < m; i++) cout << a[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
