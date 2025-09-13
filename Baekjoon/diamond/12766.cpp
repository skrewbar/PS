#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, less<T>>;

vector<pair<int, int>> adj[5050];
vector<pair<int, int>> rev_adj[5050];

int distFromHead[5050], distToHead[5050];
ll roundDistPrefSum[5050];

void findMinDistFrom(int vertex,
                     int n,
                     vector<pair<int, int>> adjList[],
                     int dist[]) {
    fill(dist + 1, dist + n + 1, INT_MAX);
    dist[vertex] = 0;

    MinHeap<pair<int, int>> pq;
    pq.emplace(dist[vertex], vertex);

    while (not pq.empty()) {
        auto [nowDist, now] = pq.top();
        pq.pop();

        if (nowDist > dist[now])
            continue;

        for (auto [next, len] : adjList[now]) {
            int nextDist = nowDist + len;
            if (nextDist < dist[next]) {
                dist[next] = nextDist;
                pq.emplace(nextDist, next);
            }
        }
    }
}

ll cost(int i, int j) {
    return (j - i) * (roundDistPrefSum[j] - roundDistPrefSum[i - 1]);
}

ll dp[5050][5050];

void divideAndConquer(int t, int s, int e, int l, int r) {
    if (s > e)
        return;

    int m = (s + e) >> 1;
    int opt = l;

    dp[t][m] = dp[t - 1][opt - 1] + cost(opt, m);
    for (int i = opt + 1; i <= r; i++) {
        if (dp[t - 1][i - 1] + cost(i, m) < dp[t][m]) {
            dp[t][m] = dp[t - 1][i - 1] + cost(i, m);
            opt = i;
        }
    }

    divideAndConquer(t, s, m - 1, l, opt);
    divideAndConquer(t, m + 1, e, opt, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b, s, r;
    cin >> n >> b >> s >> r;
    while (r--) {
        int u, v, l;
        cin >> u >> v >> l;

        adj[u].emplace_back(v, l);
        rev_adj[v].emplace_back(u, l);
    }

    findMinDistFrom(b + 1, n, adj, distFromHead);
    findMinDistFrom(b + 1, n, rev_adj, distToHead);
    for (int i = 1; i <= b; i++)
        roundDistPrefSum[i] = distFromHead[i] + distToHead[i];
    sort(roundDistPrefSum + 1, roundDistPrefSum + b + 1);
    for (int i = 1; i <= b; i++)
        roundDistPrefSum[i] += roundDistPrefSum[i - 1];

    for (int i = 1; i <= b; i++)
        dp[1][i] = cost(1, i);
    for (int t = 2; t <= s; t++)
        divideAndConquer(t, 1, b, 1, b);

    cout << dp[s][b];

    return 0;
}