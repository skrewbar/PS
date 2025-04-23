#include <bits/stdc++.h>
using namespace std;


int dfs(
    int v, // vertex
    bool bRoot,
    int &visitedCount,
    vector<vector<int>> &adj,
    vector<int> &visitOrder,
    vector<bool> &bCut
) {
    visitOrder[v] = visitedCount++;
    int ret = visitOrder[v];
    int child = 0;
    for (int next : adj[v]) {
        if (visitOrder[next] == -1) {
            child++;
            int res = dfs(next, false, visitedCount, adj, visitOrder, bCut);
            if (not bRoot and res >= visitOrder[v]) {
                bCut[v] = true;
            }
            ret = min(ret, res);
        } else {
            ret = min(ret, visitOrder[next]);
        }
    }
    if (bRoot and child >= 2) {
        bCut[v] = true;
    }

    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e;
    cin >> v >> e;

    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> visitOrder(v, -1);
    vector<bool> bCut(v);

    for (int i = 0; i < v; i++) {
        if (visitOrder[i] == -1) {
            int visitedCount = 0;
            dfs(i, true, visitedCount, adj, visitOrder, bCut);
        }
    }

    int answer = 0;
    for (int i = 0; i < v; i++) {
        if (bCut[i]) answer++;
    }
    cout << answer << '\n';
    for (int i = 0; i < v; i++) {
        if (bCut[i]) cout << i + 1 << ' ';
    }
}