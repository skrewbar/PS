#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

vector<pair<int, int>> childs[40001];
int parent[400001][20];
int parentDist[400001][20];
int depth[40001];
bool visited[40001];


void init(int now) {
    for (pair<int, int> p : childs[now]) {
        int child = p.first;
        int dist = p.second;
        if (visited[child]) continue;

        depth[child] = depth[now] + 1;
        visited[child] = true;

        parent[child][0] = now;
        parentDist[child][0] = p.second;

        for (int j = 0; j < 20; j++) {
            parent[child][j+1] = parent[parent[child][j]][j];
            parentDist[child][j+1] = parentDist[child][j] + parentDist[parent[child][j]][j];
            if (parent[child][j+1] == 0) break;
        }

        init(child);
    }
}


int getDist(int u, int v) {
    int dist = 0;
    if (depth[u] < depth[v]) swap(u, v);

    while (depth[u] != depth[v]) {
        int diff = depth[u] - depth[v];

        for (int i = 0; i < 20; i++) {
            if (diff <= 1 << (i+1)) {
                dist += parentDist[u][i];
                u = parent[u][i];
                break;
            }
        }
    }

    while (u != v) {
        for (int i = 0; i < 20; i++) {
            if (parent[u][i+1] == parent[v][i+1]) {
                dist += parentDist[u][i] + parentDist[v][i];
                u = parent[u][i];
                v = parent[v][i];
                break;
            }
        }
    }
    return dist;
}


int main() {
    fastio();

    int n;
    cin >> n;

    for (int i = 0; i < n-1; i++) {
        int a, b, dist;
        cin >> a >> b >> dist;
        childs[a].push_back({b, dist});
        childs[b].push_back({a, dist});
    }

    depth[1] = 1;
    visited[1] = true;
    init(1);


    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << getDist(u, v) << '\n';
    }

    return 0;
}