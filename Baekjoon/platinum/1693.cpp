#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = INT_MAX;

vector<int> adj[100'100];

constexpr int maxColor = 17;
int cost[100'100][maxColor + 1];

void solve(int node, int parent) {
    for (int child : adj[node]) {
        if (child == parent)
            continue;

        solve(child, node);
    }

    for (int nodeColor = 1; nodeColor <= maxColor; nodeColor++) {
        cost[node][nodeColor] = nodeColor;

        for (int child : adj[node]) {
            if (child == parent)
                continue;

            int minChildCost = INF;
            for (int childColor = 1; childColor <= maxColor; childColor++) {
                if (childColor == nodeColor)
                    continue;
                minChildCost = min(minChildCost, cost[child][childColor]);
            }

            ASSERT(minChildCost != INF);
            cost[node][nodeColor] += minChildCost;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    solve(1, -1);

    int ans = INF;
    for (int c = 1; c <= maxColor; c++)
        ans = min(ans, cost[1][c]);

    cout << ans;

    return 0;
}