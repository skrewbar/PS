#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int find_parent(int u) {
    int p = parent[u];
    while (p != parent[p]) p = parent[p];
    return parent[u] = p;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int g, p;
    cin >> g >> p;

    parent.resize(g+1);
    for (int i = 1; i <= g; i++) parent[i] = i;
    int ans = 0;
    while (p--) {
        int high_bound;
        cin >> high_bound;

        int gate = find_parent(high_bound);
        if (gate == 0) break;
        parent[gate] = find_parent(gate-1);
        ans++;
    }
    cout << ans;
}