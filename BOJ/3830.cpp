#include <bits/stdc++.h>
using namespace std;


vector<int> parent;
vector<long long> weight;

int findParent(int v) {
    if (v == parent[v]) return v;
    int root = findParent(parent[v]);
    weight[v] += weight[parent[v]];
    return parent[v] = root;
}

// v is heavier than u
void unionParent(int u, int v, int w) {
    int uRoot = findParent(u), vRoot = findParent(v);
    long long offset = w + weight[u] - weight[v];

    parent[vRoot] = uRoot;
    weight[vRoot] = offset;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 or m == 0) return 0;

        parent = vector(n+1, 0);
        weight = vector(n+1, 0LL);
        for (int i = 1; i <= n; i++) parent[i] = i;

        while (m--) {
            char q;
            cin >> q;

            if (q == '!') {
                int a, b, w;
                cin >> a >> b >> w;
                unionParent(a, b, w);
            } else {
                int a, b;
                cin >> a >> b;
                if (findParent(a) == findParent(b)) cout << weight[b] - weight[a] << '\n';
                else cout << "UNKNOWN\n";
            }
        }
    }
}