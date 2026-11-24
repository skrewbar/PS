#include <bits/stdc++.h>
#include <queue>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

vector<pair<int, int>> adj[1010];
priority_queue<int> times[1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].emplace_back(b, c);
    }

    MinHeap<pair<int, int>> pq;
    times[1].push(0);
    pq.emplace(0, 1);

    while (not pq.empty()) {
        auto [nowTime, now] = pq.top();
        pq.pop();

        for (auto [next, edgeTime] : adj[now]) {
            int nextTime = nowTime + edgeTime;

            if (times[next].size() != k or nextTime < times[next].top()) {
                if (times[next].size() == k)
                    times[next].pop();

                times[next].push(nextTime);
                pq.emplace(nextTime, next);
            }
        }
    }

    for (int i = 1; i <= n; i++)
        println("{}", (times[i].size() == k ? times[i].top() : -1));

    return 0;
}