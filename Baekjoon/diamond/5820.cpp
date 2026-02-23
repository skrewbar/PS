#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

int N, K;

struct Edge {
    int to, length;
};

vector<Edge> adj[202020];
int sz[202020];
bool removed[202020];

int minDepth[1010101];
vector<int> updatedDist;

int getSize(int cur, int parent) {
    sz[cur] = 1;

    for (auto [child, _] : adj[cur]) {
        if (child == parent or removed[child])
            continue;

        sz[cur] += getSize(child, cur);
    }

    return sz[cur];
}

int getCentroid(int cur, int parent, int treeSize) {
    for (auto [child, _] : adj[cur]) {
        if (child == parent or removed[child])
            continue;

        if (2 * sz[child] > treeSize)
            return getCentroid(child, cur, treeSize);
    }

    return cur;
}

int findMinDepth(int cur, int parent, int dist, int depth) {
    if (dist > K)
        return INF;

    int ret = INF;
    ret = min(ret, depth + minDepth[K - dist]);

    for (auto [child, length] : adj[cur]) {
        if (child == parent or removed[child])
            continue;

        ret = min(ret, findMinDepth(child, cur, dist + length, depth + 1));
    }

    return ret;
}

void updateMinDepth(int cur, int parent, int dist, int depth) {
    if (dist > K)
        return;

    if (minDepth[dist] == INF)
        updatedDist.push_back(dist);
    minDepth[dist] = min(minDepth[dist], depth);

    for (auto [child, length] : adj[cur]) {
        if (child == parent or removed[child])
            continue;

        updateMinDepth(child, cur, dist + length, depth + 1);
    }
}

int dnc(int cur) {
    int treeSize = getSize(cur, -1);
    int centroid = getCentroid(cur, -1, treeSize);
    removed[centroid] = true;

    int ret = INF;

    for (int d : updatedDist)
        minDepth[d] = INF;
    updatedDist.clear();
    minDepth[0] = 0;

    for (auto [child, length] : adj[centroid]) {
        if (removed[child])
            continue;

        ret = min(ret, findMinDepth(child, centroid, length, 1));
        updateMinDepth(child, centroid, length, 1);
    }

    for (auto [child, _] : adj[centroid]) {
        if (removed[child])
            continue;

        ret = min(ret, dnc(child));
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    for (int i = 0; i < N - 1; i++) {
        int u, v, l;
        cin >> u >> v >> l;

        adj[u].emplace_back(v, l);
        adj[v].emplace_back(u, l);
    }

    fill(minDepth, minDepth + K + 1, INF);

    int ans = dnc(0);
    if (ans == INF)
        println("-1");
    else
        println("{}", ans);

    return 0;
}