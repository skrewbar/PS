#include <bits/stdc++.h>
using namespace std;

vector<int> adj[202020];
bool isSpecial[202020];
bool isOpen[202020];

int dfs(int v, int p) {
    int ret = 0;
    int spTreeCnt = 0;
    int openCnt = 0;

    for (int c : adj[v]) {
        if (c == p) continue;

        ret += dfs(c, v);
        if (not isSpecial[c]) continue;

        spTreeCnt++;
        openCnt += isOpen[c];
    }

    if (spTreeCnt == 0) {
        isOpen[v] = true;
        return 0;
    }

    if (openCnt >= 2) spTreeCnt -= 1;
    else if (openCnt == 1) isOpen[v] = true;
    else if (isSpecial[v]) {
        isOpen[v] = true;
        spTreeCnt++;
    }

    if (spTreeCnt) isSpecial[v] = true;
    ret += max(0, spTreeCnt - 1);

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; i++) cin >> isSpecial[i];

    cout << dfs(1, 0);

    return 0;
}
