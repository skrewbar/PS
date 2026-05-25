#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

int a[202020], maxDepth[202020];
ll sum[202020], cost[202020], answer[202020];
vector<vector<int>> adj;

void removeParent(int cur, int parent) {
    for (int &child : adj[cur]) {
        if (child == parent) {
            swap(adj[cur].back(), child);
            adj[cur].pop_back();
            break;
        }
    }

    for (int child : adj[cur]) removeParent(child, cur);
}

void dfs(int cur, int depth) {
    sum[cur] = a[cur];
    cost[cur] = 0;
    maxDepth[cur] = depth;

    int childCnt = adj[cur].size();
    if (childCnt == 0) return;

    for (int i = 0; i < childCnt; i++) {
        int child = adj[cur][i];

        dfs(child, depth + 1);
        cost[cur] += cost[child] + sum[child];
        sum[cur] += sum[child];
        maximize(maxDepth[cur], maxDepth[child]);
    }

    vector<int> pref, suff;
    pref = suff = vector<int>(childCnt);

    pref[0] = maxDepth[adj[cur].front()];
    for (int i = 1; i < childCnt; i++)
        pref[i] = max(pref[i - 1], maxDepth[adj[cur][i]]);

    suff[childCnt - 1] = maxDepth[adj[cur].back()];
    for (int i = childCnt - 2; i >= 0; i--)
        suff[i] = max(suff[i + 1], maxDepth[adj[cur][i]]);

    for (int i = 0; i < childCnt; i++) {
        int child = adj[cur][i];

        int mxDep = depth;
        if (i - 1 >= 0) maximize(mxDep, pref[i - 1]);
        if (i + 1 < childCnt) maximize(mxDep, suff[i + 1]);

        maximize(answer[cur], cost[cur] + sum[child] * (mxDep - depth));
        maximize(answer[cur], cost[cur] + answer[child] - cost[child]);
    }
}

void solve() {
    int n;
    cin >> n;

    adj.assign(n + 1, vector<int>());

    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    removeParent(1, -1);

    fill(answer, answer + n + 1, 0);
    dfs(1, 0);

    for (int i = 1; i <= n; i++) cout << answer[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
