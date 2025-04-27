#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> adj;
vector<bool> finished;
vector<int> visitOrder;
vector<bool> answer;
stack<int> s;

int visitedCount = 0;
bool canSolve = true;


int findSCC(int v) {
    s.push(v);
    visitOrder[v] = visitedCount++;
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
            int top = s.top();
            s.pop();
            finished[top] = true;
            SCC.insert(top);

            if (not finished[top ^ 1]) answer[top / 2] = top & 1;

            if (SCC.contains(top ^ 1)) canSolve = false;
            if (top == v) break;
        }
    }

    return lowLinkValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj = vector<vector<int>>(2*n);
    for (int k = 0; k < m; k++) {
        int i, j;
        cin >> i >> j;
        i = 2 * (abs(i) - 1) + (i > 0);
        j = 2 * (abs(j) - 1) + (j > 0);

        adj[i ^ 1].push_back(j);
        adj[j ^ 1].push_back(i);
    }

    finished = vector(2*n, false);
    visitOrder = vector(2*n, -1);
    answer = vector(n, false);
    
    for (int i = 0; i < 2*n; i++) {
        if (not finished[i]) findSCC(i);
        if (not canSolve) break;
    }

    cout << canSolve << '\n';
    
    if (canSolve) {
        for (bool b : answer) cout << b << ' ';
    }
}