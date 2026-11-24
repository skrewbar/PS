#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<bool> visited;
vector<vector<pair<int, int>>> adj;
vector<int> diameter, radius, treeNum;
vector<vector<int>> forest;
int treeCnt = 0;

void classifyTrees(int node, int parent) {
    visited[node] = true;
    forest[treeCnt].push_back(node);

    for (auto [child, _] : adj[node]) {
        if (child == parent)
            continue;

        classifyTrees(child, node);
    }
}

void setDistFrom(int node, int parent, vector<int>& dist) {
    for (auto [child, d] : adj[node]) {
        if (child == parent)
            continue;

        dist[child] = dist[node] + d;
        setDistFrom(child, node, dist);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l;
    cin >> n >> m >> l;

    visited = vector(n, false);
    adj = vector(n, vector<pair<int, int>>());
    diameter = radius = treeNum = vector(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;

        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t);
    }

    vector<int> roots;
    for (int i = 0; i < n; i++) {
        if (visited[i])
            continue;

        roots.push_back(i);
        forest.emplace_back();
        classifyTrees(i, i);
        treeCnt++;
    }

    vector<int> distFromRoot(n), distFromFar1(n), distFromFar2(n);
    for (int t = 0; t < treeCnt; t++) {
        int root = roots[t];

        distFromRoot[root] = 0;
        setDistFrom(root, root, distFromRoot);
        int far1 = root;
        for (int node : forest[t]) {
            if (distFromRoot[node] > distFromRoot[far1])
                far1 = node;
        }

        distFromFar1[far1] = 0;
        setDistFrom(far1, far1, distFromFar1);
        int far2 = far1;
        for (int node : forest[t]) {
            if (distFromFar1[node] > distFromFar1[far2])
                far2 = node;
        }

        distFromFar2[far2] = 0;
        setDistFrom(far2, far2, distFromFar2);

        diameter[t] = distFromFar1[far2];
        radius[t] = diameter[t];
        for (int node : forest[t])
            radius[t] =
                min(radius[t], max(distFromFar1[node], distFromFar2[node]));
    }

    ranges::sort(diameter, greater<>());
    ranges::sort(radius, greater<>());
    int answer = diameter.front();
    if (treeCnt >= 2)
        answer = max(answer, radius[0] + l + radius[1]);
    if (treeCnt >= 3)
        answer = max(answer, radius[1] + l + l + radius[2]);

    cout << answer;

    return 0;
}