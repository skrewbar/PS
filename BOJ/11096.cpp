#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) { iota(all(parent), 0); }

    int findParent(int x) {
        if (x != parent[x])
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);

        if (u != v)
            parent[v] = u;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

struct Circle {
    int x, y, r;

    bool isOverlap(const Circle& c) {
        int dx = x - c.x;
        int dy = y - c.y;
        int rr = r + c.r;

        return dx*dx + dy*dy < rr*rr;
    }
};

Circle circle[222];

constexpr int width = 200;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int lWall = 0, rWall = N + 1;
    DisjointSet ds(N + 2);
    
    int answer = 0;
    for (int i = 1; i <= N; i++) {
        auto& [x, y, r] = circle[i];
        cin >> x >> y >> r;
        
        if (x - r <= 0)
            ds.unionParent(lWall, i);
        if (x + r >= width)
            ds.unionParent(rWall, i);
        
        for (int j = 1; j < i; j++) {
            if (not circle[i].isOverlap(circle[j]))
                continue;

            ds.unionParent(i, j);
        }
        
        if (ds.isConnected(lWall, rWall))
            break;
        answer = i;
    }
    
    cout << answer;

    return 0;
}