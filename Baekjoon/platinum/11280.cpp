#include <bits/stdc++.h>
using namespace std;

int n, m;

// returns index of boolean variable
int normalized(int x) {
    if (x < 0) return -x + n;
    return x;
}
// returns index of logical not
int lnot(int x) {
    return (x > n ? x - n : x + n);
}

vector<vector<int>> adj;
vector<int> visitOrder;
vector<bool> finished;
stack<int> s;
int visitedCount = 0;
bool canSolve = true;

int findSCC(int v) {
    visitOrder[v] = visitedCount++;
    int lowLinkValue = visitOrder[v];
    s.push(v);

    for (int next : adj[v]) {
        if (finished[next]) continue;
        if (visitOrder[next] == -1) {
            lowLinkValue = min(lowLinkValue, findSCC(next));
        } else {
            lowLinkValue = min(lowLinkValue, visitOrder[next]);
        }
    }

    if (lowLinkValue == visitOrder[v]) { // if v is root of SCC
        set<int> SCC;
        while (true) {
            int top = s.top();
            s.pop();
            finished[top] = true;
            if (SCC.contains(lnot(top))) canSolve = false;
            SCC.insert(top);
            if (top == v) break;
        }
    }
    return lowLinkValue;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;

    adj = vector<vector<int>>(2 * n + 1);
    visitOrder = vector(2 * n + 1, -1);
    finished = vector(2 * n + 1, false);

    for (int k = 0; k < m; k++) {
        int i, j;
        cin >> i >> j;
        i = normalized(i);
        j = normalized(j);
        adj[lnot(i)].push_back(j);
        adj[lnot(j)].push_back(i);
    }

    for (int i = 1; i <= 2 * n; i++) {
        if (not finished[i]) findSCC(i);
        if (not canSolve) break;
    }

    cout << canSolve;
}