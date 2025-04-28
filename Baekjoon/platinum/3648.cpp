#include <bits/stdc++.h>
using namespace std;


int normalized(int x) {
    if (x < 0) return (-x << 1) - 2;
    return (x << 1) - 1;
}
int lnot(int x) {
    return x ^ 1;
}


vector<vector<int>> adj;
vector<bool> finished;
vector<int> visitOrder;
stack<int> s;
int visitedCount;
bool canSolve;

int findSCC(int v) {
    s.push(v);

    visitOrder[v] = ++visitedCount;
    int lowLinkValue = visitOrder[v];

    for (int neighbor : adj[v]) {
        if (finished[neighbor]) continue;

        if (visitOrder[neighbor] == -1) {
            lowLinkValue = min(lowLinkValue, findSCC(neighbor));
        } else {
            lowLinkValue = min(lowLinkValue, visitOrder[neighbor]);
        }
    }

    if (lowLinkValue == visitOrder[v]) {
        set<int> SCC;
        while (true) {
            int u = s.top();
            s.pop();
            finished[u] = true;
            if (SCC.contains(lnot(u))) canSolve = false;
            SCC.insert(u);
            if (u == v) break;
        }
    }

    return lowLinkValue;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    while (cin >> n >> m) {
        adj = vector<vector<int>>(n << 1);
        finished = vector(n << 1, false);
        visitOrder = vector(n << 1, -1);
        s = stack<int>();
        visitedCount = 0;
        canSolve = true;

        adj[0].push_back(1);  // 상근이가 진출하지 못한다면 모순
        while (m--) {
            int a, b;
            cin >> a >> b;
            a = normalized(a);
            b = normalized(b);
            
            adj[lnot(a)].push_back(b);
            adj[lnot(b)].push_back(a);
        }

        for (int i = 0; i < (n << 1); i++) {
            if (not finished[i]) findSCC(i);
            if (not canSolve) break;
        }

        cout << (canSolve ? "yes" : "no") << '\n';
    }
}