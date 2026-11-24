#include <bits/stdc++.h>
using namespace std;


vector<set<int>> adj;
vector<bool> finished;
vector<int> visitOrder;
stack<int> s;
int visitedCount = 0;
int sccCount = 0;

vector<int> sccNumber;

int findSCC(int v) {
    s.push(v);
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
        while (true) {
            int u = s.top();
            s.pop();

            finished[u] = true;
            sccNumber[u] = sccCount;
            if (u == v) break;
        }
        sccCount++;
    }

    return lowLink;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj = vector(n, set<int>());
    for (int i = 0; i < m; i++) {
        int v, w;
        cin >> v >> w;
        v--, w--;

        adj[v].insert(w);
    }

    finished = vector(n, false);
    visitOrder = vector(n, -1);
    sccNumber = vector(n, -1);

    for (int i = 0; i < n; i++) {
        if (not finished[i]) findSCC(i);
    }

    vector<set<int>> sccAdj = vector(sccCount, set<int>());
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (sccNumber[i] != sccNumber[j]) {
                sccAdj[sccNumber[i]].insert(sccNumber[j]);
            }
        }
    }

    vector<int> indegree(sccCount);
    for (int i = 0; i < sccCount; i++) {
        for (int j : sccAdj[i]) indegree[j]++;
    }

    queue<int> q;
    for (int i = 0; i < sccCount; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    int canVisitAll = true;
    while (not q.empty()) {
        if (q.size() >= 2) {
            canVisitAll = false;
            break;
        }

        int scc = q.front();
        q.pop();

        for (int neighbor : sccAdj[scc]) {
            if (--indegree[neighbor] == 0) q.push(neighbor);
        }
    }

    if (not canVisitAll) {
        cout << 0;
        return 0;
    }

    set<int> answer;
    for (int i = 0; i < n; i++) {
        if (sccNumber[i] == sccCount - 1) answer.insert(i);
    }

    cout << answer.size() << '\n';
    for (int v : answer) cout << v + 1 << ' ';
}