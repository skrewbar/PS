#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<vector<int>> adj, binParent;
vector<int> depth;

void setup(int node, int parent) {
    for (int child : adj[node]) {
        if (child == parent)
            continue;

        depth[child] = depth[node] + 1;
        binParent[child][0] = node;
        for (int i = 1; i < 20; i++)
            binParent[child][i] = binParent[binParent[child][i - 1]][i - 1];
        setup(child, node);
    }
}

int getLCA(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];
    for (int i = 0; i < 20; i++) {
        if (diff & (1 << i))
            u = binParent[u][i];
    }

    if (u != v) {
        for (int i = 19; i >= 0; i--) {
            if (binParent[u][i] != binParent[v][i])
                u = binParent[u][i], v = binParent[v][i];
        }
        u = binParent[u][0];
    }

    return u;
}

int getDist(int u, int v) {
    int lca = getLCA(u, v);
    return abs(depth[lca] - depth[u]) + abs(depth[lca] - depth[v]);
}

int middleVertex(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int dist = getDist(u, v);
    if (dist & 1)
        return -1;

    dist >>= 1;
    for (int i = 0; i < 20; i++)
        if (dist & (1 << i))
            u = binParent[u][i];

    return u;
}

int getCircumcenter(int a, int b, int c) {
    for (auto m :
         {middleVertex(a, b), middleVertex(b, c), middleVertex(c, a)}) {
        if (m == -1)
            continue;
        if (getDist(m, a) == getDist(m, b) and getDist(m, b) == getDist(m, c))
            return m;
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj = vector(n + 1, vector<int>());
    binParent = vector(n + 1, vector(20, 0));
    depth = vector(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    setup(1, 0);

    int q;
    cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << getCircumcenter(a, b, c) << '\n';
    }

    return 0;
}