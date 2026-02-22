#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

vector<int> adj[202020];
int depth[202020], maxDepth[202020];

void sortAdjByMaxDepth(int at, int parent) {
    for (int child : adj[at]) {
        if (child == parent)
            continue;

        maxDepth[child] = depth[child] = depth[at] + 1;
        sortAdjByMaxDepth(child, at);

        maxDepth[at] = max(maxDepth[at], maxDepth[child]);
    }

    sort(adj[at].begin(), adj[at].end(),
         [&](int i, int j) { return maxDepth[i] > maxDepth[j]; });
}

void printDfs(int at, int parent) {
    for (int child : adj[at]) {
        if (child == parent)
            continue;

        printDfs(child, at);
    }

    print("{} ", at);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    sortAdjByMaxDepth(1, -1);
    printDfs(1, -1);

    return 0;
}