#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

int dp[20][1 << 20];
int previous[20], distToEnd[20], distFromEnd[20];
vector<pair<int, int>> adj[20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> previous[i];
        previous[i]--;
    }

    fill(distFromEnd, distFromEnd + 20, INF);
    fill(distToEnd, distToEnd + 20, INF);
    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;

        if (u == N)
            distFromEnd[v] = min(distFromEnd[v], w);
        else if (v == N)
            distToEnd[u] = min(distToEnd[u], w);
        else
            adj[u].emplace_back(v, w);
    }

    fill(&dp[0][0], &dp[N][1 << N], INF);
    for (int i = 0; i < N; i++)
        if (previous[i] == i)
            dp[i][1 << i] = distFromEnd[i];
    for (int visited = 0; visited < 1 << N; visited++) {
        for (int i = 0; i < N; i++) {
            if (~visited & (1 << i))
                continue;

            for (auto [nxt, time] : adj[i]) {
                if (visited & (1 << nxt))
                    continue;
                if (previous[nxt] != nxt and ~visited & (1 << previous[nxt]))
                    continue;

                dp[nxt][visited | (1 << nxt)] =
                    min(dp[nxt][visited | (1 << nxt)], dp[i][visited] + time);
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < N; i++)
        ans = min(ans, dp[i][(1 << N) - 1] + distToEnd[i]);

    println("{}", (ans == INF ? -1 : ans));

    return 0;
}