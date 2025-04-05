#include <bits/stdc++.h>
using namespace std;


vector<int> energes;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> parent;
vector<vector<int>> dist;
vector<int> depth;
vector<int> visited;

void setupDist(int now) {
    for (auto [next, cost] : adj[now]) {
        if (visited[next]) continue;
        visited[next] = true;
        
        parent[next][0] = now;
        dist[next][0] = cost;
        depth[next] = depth[now] + 1;

        for (int i = 1; i < 18; i++) {
            if (parent[next][i-1] == 0) break;
            parent[next][i] = parent[parent[next][i-1]][i-1];
            dist[next][i] = dist[next][i-1] + dist[parent[next][i-1]][i-1];
        }

        setupDist(next);
    }
}

// 1번방을 향해 최대 몇 번 갈 수 있는지
int upperBoundCeil(int x) {
    int lo = 0, hi = depth[x] + 1; // 몇 번까지 움직일 수 있는지 [lo, hi)

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int length = 0;

        int now = x;
        for (int i = 0; i < 18; i++) {
            if (mid & (1 << i)) {
                length += dist[now][i];
                now = parent[now][i];
            }
        }

        if (length <= energes[x]) lo = mid + 1;
        else hi = mid;
    }
    lo--;
    
    int ret = x;
    for (int i = 0; i < 18; i++) {
        if (lo & (1 << i)) ret = parent[ret][i];
    }
    return ret;
}

int main() {
    // NOTE: 1번이 아니라 0번
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    energes.resize(n);
    for (int i = 0; i < n; i++) cin >> energes[i];

    adj.assign(n, vector<pair<int, int>>());
    for (int i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    parent.resize(n, vector<int>(18)); // 2^17 = 131072이기 때문 
    dist.resize(n, vector<int>(18));
    depth.resize(n);
    visited.resize(n);

    visited[0] = true;
    setupDist(0);
    for (int i = 0; i < n; i++) {
        cout << upperBoundCeil(i) + 1 << '\n';
    }
}