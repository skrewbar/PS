#include "race.h"
#include <map>
#include <vector>
using namespace std;

using ll = long long;

constexpr ll INF = 1e9;

#define all(v) (v).begin(), (v).end()
#define contains(s, x) (s).find(x) != (s).end()

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

vector<pair<int, ll>> adj[202020];
int sz[202020];
bool finished[202020];

void findSize(int cur, int parent) {
    sz[cur] = 1;

    for (auto [child, _] : adj[cur]) {
        if (child == parent or finished[child])
            continue;

        findSize(child, cur);
        sz[cur] += sz[child];
    }
}

int findCentroid(int cur, int parent, int treeSize) {
    for (auto [child, _] : adj[cur]) {
        if (child == parent or finished[child])
            continue;

        if (sz[child] > treeSize / 2)
            return findCentroid(child, cur, treeSize);
    }

    return cur;
}

map<ll, int> minCnt;

int findAnswer(int cur, int parent, ll lenSum, int depth, int K) {
    int ret = INF;

    if (minCnt.find(K - lenSum) != minCnt.end())
        minimize(ret, depth + minCnt[K - lenSum]);

    for (auto [child, len] : adj[cur]) {
        if (child == parent or finished[child])
            continue;
        
        minimize(ret, findAnswer(child, cur, lenSum + len, depth + 1, K));
    }

    return ret;
}
void findMinCnt(int cur, int parent, ll lenSum, int depth) {
    if (minCnt.find(lenSum) == minCnt.end()) {
        minCnt[lenSum] = depth;
    } else
        minimize(minCnt[lenSum], depth);

    for (auto [child, len] : adj[cur]) {
        if (child == parent or finished[child])
            continue;

        findMinCnt(child, cur, lenSum + len, depth + 1);
    }
}

int dnc(int cur, int parent, int K) {
    findSize(cur, parent);
    int centroid = findCentroid(cur, parent, sz[cur]);

    int ret = INF;
    minCnt.clear();
    minCnt[0] = 0;
    for (auto [child, len] : adj[centroid]) {
        if (finished[child])
            continue;

        minimize(ret, findAnswer(child, centroid, len, 1, K));
        findMinCnt(child, centroid, len, 1);
    }
    
    finished[centroid] = true;
    for (auto [child, _] : adj[centroid]) {
        if (finished[child])
            continue;

        minimize(ret, dnc(child, centroid, K));
    }

    return ret;
}

int best_path(int N, int K, int H[][2], int L[]) {
    for (int i = 0; i < N - 1; i++) {
        auto [u, v] = H[i];
        adj[u].emplace_back(v, L[i]);
        adj[v].emplace_back(u, L[i]);
    }

    int ans = dnc(0, -1, K);

    return (ans == INF ? -1 : ans);
}
