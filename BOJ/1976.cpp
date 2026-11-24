#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int find_parent(int x) {
    if (x != parent[x]) parent[x] = find_parent(parent[x]);
    return parent[x];
}

void union_parent(int u, int v) {
    parent[find_parent(u)] = find_parent(v);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    parent.resize(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int connected;
            cin >> connected;
            if (connected) union_parent(i, j);
        }
    }

    int begin;
    cin >> begin;
    begin--;
    for (int i = 0; i < m-1; i++) {
        int travel;
        cin >> travel;
        travel--;

        if (find_parent(begin) != find_parent(travel)) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}