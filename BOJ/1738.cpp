#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

struct Edge {
    int u, v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<int>> revAdj(n + 1, vector<int>());
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        revAdj[v].push_back(u);
    }

    // Check whether hotel (vertex n) is reachable from each vertex
    vector<bool> canReachToHotel(n + 1);
    canReachToHotel[n] = true;

    queue<int> q;
    q.push(n);

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (int nxt : revAdj[now]) {
            if (canReachToHotel[nxt])
                continue;
            canReachToHotel[nxt] = true;
            q.push(nxt);
        }
    }

    // Find the maximum money and the previous vertex for each vertex on the optimal path
    vector<ll> money(n + 1, LLONG_MIN);
    money[1] = 0;

    vector<int> prev(n + 1);

    for (int i = 0; i < n; i++) {
        for (auto& [u, v, w] : edges) {
            if (money[u] == LLONG_MIN)
                continue;

            if (money[u] + w > money[v]) {
                money[v] = money[u] + w;
                prev[v] = u;
            }
        }
    }

    // Check if a positive cycle exists on the path to the hotel
    bool hasCycleOnPath = false;
    for (auto& [u, v, w] : edges) {
        if (money[u] == LLONG_MIN or not canReachToHotel[v])
            continue;

        if (money[u] + w > money[v])
            hasCycleOnPath = true;
    }

    if (hasCycleOnPath or money[n] == LLONG_MIN) {
        cout << -1;
    } else {
        stack<int> ans;
        for (int i = n; i != 1; i = prev[i])
            ans.push(i);

        cout << 1 << ' ';
        while (not ans.empty()) {
            cout << ans.top() << ' ';
            ans.pop();
        }
    }

    return 0;
}