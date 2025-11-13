#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> adj[101010];
int visitOrder[101010], sccNum[101010];
bool finished[101010];
int visitedCnt, sccCnt;

stack<int> stk;

int findSCC(int now) {
    stk.push(now);
    int lowLink = visitOrder[now] = visitedCnt++;

    for (int next : adj[now]) {
        if (finished[next])
            continue;

        int nextLow = visitOrder[next];
        if (nextLow == -1)
            nextLow = findSCC(next);

        lowLink = min(lowLink, nextLow);
    }

    if (lowLink == visitOrder[now]) {
        while (true) {
            int top = stk.top();
            stk.pop();

            finished[top] = true;
            sccNum[top] = sccCnt;

            if (top == now)
                break;
        }
        sccCnt++;
    }

    return lowLink;
}

void solve() {
    int N, M;
    cin >> N >> M;

    fill(adj + 1, adj + N + 1, vector<int>());
    fill(visitOrder + 1, visitOrder + N + 1, -1);
    fill(sccNum + 1, sccNum + N + 1, -1);
    fill(finished + 1, finished + N + 1, false);
    visitedCnt = sccCnt = 0;

    while (M--) {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
    }

    for (int i = 1; i <= N; i++)
        if (not finished[i])
            findSCC(i);

    vector<vector<int>> sccAdj = vector(sccCnt, vector<int>());
    for (int i = 1; i <= N; i++) {
        for (int j : adj[i]) {
            if (sccNum[i] != sccNum[j])
                sccAdj[sccNum[i]].push_back(sccNum[j]);
        }
    }

    int ans = 0;
    vector<bool> fallDown(sccCnt);
    for (int i = sccCnt - 1; i >= 0; i--) {
        if (not fallDown[i])
            ans++;

        for (int j : sccAdj[i])
            fallDown[j] = true;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}