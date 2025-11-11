#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;
constexpr ll INF = 1e15;

int N, M;
vector<vector<int>> adj;
vector<tuple<int, int, ll>> edges;
vector<ll> money, total;

bool reachable(int from, int to) {
    vector<bool> visited(N);

    queue<int> q;
    q.push(from);

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (int nxt : adj[now]) {
            if (nxt == to)
                return true;

            if (visited[nxt])
                continue;
            visited[nxt] = true;
            q.push(nxt);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int start, end;
    cin >> N >> start >> end >> M;

    adj.resize(N);
    edges.resize(M);
    for (auto& [s, e, c] : edges) {
        cin >> s >> e >> c;
        adj[s].push_back(e);
    }

    money.resize(N);
    for (int i = 0; i < N; i++)
        cin >> money[i];
    for (auto& [_, e, c] : edges)
        c = -c + money[e];

    total.resize(N, -INF);
    total[start] = money[start];

    for (int i = 0; i < N - 1; i++) {
        for (auto& [s, e, c] : edges) {
            if (total[s] != -INF)
                total[e] = max(total[e], total[s] + c);
        }
    }

    bool hasCycleToEnd = false;
    for (auto& [s, e, c] : edges) {
        if (total[s] != -INF and total[s] + c > total[e] and
            reachable(e, end)) {
            hasCycleToEnd = true;
            break;
        }
    }

    if (total[end] == -INF)
        println("gg");
    else if (hasCycleToEnd)
        println("Gee");
    else
        println("{}", total[end]);

    return 0;
}