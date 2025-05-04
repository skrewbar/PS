#include <bits/stdc++.h>
using namespace std;

constexpr bool scissors = true;

vector<vector<int>> adj;
vector<int> visitOrder;
vector<bool> finished;
stack<int> sccStack;
int visitedCount = 0;
bool canLive = true;


int findSCC(int v) {
    sccStack.push(v);
    int lowLink = visitOrder[v] = ++visitedCount;

    for (int neighbor : adj[v]) {
        if (finished[neighbor]) continue;
        if (visitOrder[neighbor] == -1) {
            lowLink = min(lowLink, findSCC(neighbor));
        } else {
            lowLink = min(lowLink, visitOrder[neighbor]);
        }
    }

    if (lowLink == visitOrder[v]) {
        set<int> scc;
        while (true) {
            int u = sccStack.top();
            sccStack.pop();

            finished[u] = true;
            scc.insert(u);
            if (scc.contains(u ^ 1)) canLive = false;
            if (u == v) break;
        }
    }

    return lowLink;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj = vector(m << 1, vector<int>());
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        x = ((abs(x) << 1) - 1) - (x < 0);
        y = ((abs(y) << 1) - 1) - (y < 0);
        adj[x ^ 1].push_back(y);
        adj[y ^ 1].push_back(x);
    }

    visitOrder = vector(m << 1, -1);
    finished = vector(m << 1, false);

    for (int i = 0; i < m << 1; i++) {
        if (not finished[i]) findSCC(i);
    }

    cout << (canLive ? "^_^" : "OTL");
}