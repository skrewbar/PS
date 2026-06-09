#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

using ll = long long;

template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

constexpr ll INF = 1e15;

vector<pair<int, ll>> adj[101010];
ll minDist[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int A, B, C;
        cin >> A >> B >> C;

        adj[A].emplace_back(B, C);
        adj[B].emplace_back(A, C);
    }

    fill(minDist + 2, minDist + N + 1, INF);

    MinHeap<pair<ll, int>> pq;
    minDist[1] = 0;
    pq.emplace(minDist[1], 1);

    while (not pq.empty()) {
        auto [curDist, cur] = pq.top();
        pq.pop();

        if (curDist > minDist[cur])
            continue;

        for (auto [nxt, edgeDist] : adj[cur]) {
            if (minimize(minDist[nxt], curDist + edgeDist)) {
                pq.emplace(minDist[nxt], nxt);
            }
        }
    }

    cout << (minDist[N] == INF ? -1 : minDist[N]);

    return 0;
}
