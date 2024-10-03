#include <bits/stdc++.h>
using namespace std;

vector<int> parent;


int findParent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent[x]);
}


void unionParent(int x, int y) {
    x = findParent(x);
    y = findParent(y);

    if (x != y) parent[x] = y;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;
    parent.resize(n);

    for (int i = 0 ; i < n ; i++) parent[i] = i;

    for (int i = 1 ; i <= m ; i++) {
        int a, b;
        cin >> a >> b;
        
        if (findParent(a) != findParent(b)) {
            unionParent(a, b);
        } else {
            cout << i;
            return 0;
        }
    }
    cout << 0;

    return 0;
}