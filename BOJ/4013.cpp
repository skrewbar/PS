#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

vector<int> adj[505050];
int cash[505050], visitOrder[505050], sccNum[505050];
bool finished[505050], isRestaurant[505050];

vector<int> totalCash;
vector<bool> hasRestaurant;
int sccCnt = 0;

stack<int> stk;

int findSCC(int now) {
    static int visitedCnt = 0;

    int lowLink = visitOrder[now] = visitedCnt++;
    stk.push(now);

    for (int next : adj[now]) {
        if (finished[next])
            continue;

        int nextLow = visitOrder[next];
        if (nextLow == -1)
            nextLow = findSCC(next);
        lowLink = min(lowLink, nextLow);
    }

    if (lowLink == visitOrder[now]) {
        totalCash.push_back(0);
        hasRestaurant.push_back(false);

        while (true) {
            int top = stk.top();
            stk.pop();

            finished[top] = true;
            sccNum[top] = sccCnt;

            totalCash.back() += cash[top];
            hasRestaurant.back() = hasRestaurant.back() or isRestaurant[top];

            if (top == now)
                break;
        }

        sccCnt++;
    }

    return lowLink;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    fill(visitOrder + 1, visitOrder + N + 1, -1);

    while (M--) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
    }

    for (int i = 1; i <= N; i++)
        cin >> cash[i];

    int S, P;
    cin >> S >> P;

    while (P--) {
        int r;
        cin >> r;

        isRestaurant[r] = true;
    }

    findSCC(S);
    
    vector<vector<int>> sccAdj(sccCnt);
    for (int i = 1; i <= N; i++) {
        for (int j : adj[i]) {
            if (sccNum[i] == sccNum[j])
                continue;

            sccAdj[sccNum[i]].push_back(sccNum[j]);
        }
    }

    vector<int> dp(sccCnt);
    dp.back() = totalCash.back();
    int ans = 0;
    for (int i = sccCnt - 1; i >= 0; i--) {
        if (hasRestaurant[i])
            ans = max(ans, dp[i]);

        for (int j : sccAdj[i])
            dp[j] = max(dp[j], dp[i] + totalCash[j]);
    }

    cout << ans;

    return 0;
}