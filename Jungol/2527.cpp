#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

int N;
ll K;

vector<pair<int, ll>> adj[202020];
int sz[202020];
bool removed[202020];

void calcSize(int cur, int parent) {
    sz[cur] = 1;

    for (auto [child, _] : adj[cur]) {
        if (child == parent or removed[child]) continue;

        calcSize(child, cur);
        sz[cur] += sz[child];
    }
}

int getCentroid(int treeSize, int cur, int parent) {
    for (auto [child, _] : adj[cur]) {
        if (child == parent or removed[child]) continue;

        if (sz[child] > treeSize / 2) return getCentroid(treeSize, child, cur);
    }

    return cur;
}

int dnc(int cur) {
    calcSize(cur, -1);
    int treeSize = sz[cur];

    int centroid = getCentroid(treeSize, cur, -1);

    map<ll, int> minEdgeCnt = {{0, 0}};
    auto addPath = [&](auto &&self, int cur, int parent, ll len,
                       int depth) -> void {
        if (minEdgeCnt.find(len) != minEdgeCnt.end())
            minimize(minEdgeCnt[len], depth);
        else minEdgeCnt[len] = depth;

        for (auto [child, edgeLen] : adj[cur]) {
            if (child == parent or removed[child]) continue;

            self(self, child, cur, len + edgeLen, depth + 1);
        }
    };
    auto getMinEdgeCnt = [&](auto &&self, int cur, int parent, ll len,
                             int depth) -> int {
        int ret = N + 1;
        if (minEdgeCnt.find(K - len) != minEdgeCnt.end())
            ret = minEdgeCnt[K - len] + depth;

        for (auto [child, edgeLen] : adj[cur]) {
            if (child == parent or removed[child]) continue;

            minimize(ret, self(self, child, cur, len + edgeLen, depth + 1));
        }

        return ret;
    };

    int ans = N + 1;

    for (auto [child, edgeLen] : adj[centroid]) {
        if (removed[child]) continue;

        minimize(ans,
                 getMinEdgeCnt(getMinEdgeCnt, child, centroid, edgeLen, 1));
        addPath(addPath, child, centroid, edgeLen, 1);
    }

    removed[centroid] = true;
    for (auto [child, edgeLen] : adj[centroid]) {
        if (removed[child]) continue;

        minimize(ans, dnc(child));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        ll l;
        cin >> u >> v >> l;

        adj[u].emplace_back(v, l);
        adj[v].emplace_back(u, l);
    }

    int ans = dnc(1);

    cout << (ans > N ? -1 : ans);

    return 0;
}