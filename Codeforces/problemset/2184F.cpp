#include <bits/stdc++.h>
using namespace std;

vector<int> adj[202020];
bool dp[202020][3];

void dfs(int cur, int parent) {
    dp[cur][1] = true;
    if (adj[cur].front() == parent and adj[cur].size() == 1)
        return;

    bool possible[3] = {true};
    for (int child : adj[cur]) {
        if (child == parent)
            continue;
        dfs(child, cur);

        bool newPossible[3] = {};

        for (int j = 0; j < 3; j++) {
            if (not possible[j])
                continue;

            for (int k = 0; k < 3; k++) {
                if (not dp[child][k])
                    continue;

                newPossible[(j + k) % 3] = true;
            }
        }

        swap(possible, newPossible);
    }

    for (int j = 0; j < 3; j++)
        dp[cur][j] |= possible[j];
}

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        adj[i].clear();
    fill(&dp[0][0], &dp[n + 5][0], false);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1);
    if (dp[1][0])
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}