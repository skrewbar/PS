#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int delta[] = {1, -1, 0, 0};

struct DisjointSet {
    vector<int> parent;

    DisjointSet(size_t size) : parent(size) {
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int findParent(int v) {
        if (parent[v] != v)
            parent[v] = findParent(parent[v]);
        return parent[v];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);
        if (u != v)
            parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

int visitedBy[2020][2020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    fill(&visitedBy[1][1], &visitedBy[N][N + 1], -1);

    queue<pair<int, int>> q;
    DisjointSet civilizations(K);
    int cnt = K;
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;

        visitedBy[x][y] = i;
        q.emplace(x, y);

        for (int k = 0; k < 4; k++) {
            int nx = x + delta[k];
            int ny = y + delta[3 - k];

            if (nx <= 0 or nx > N or ny <= 0 or ny > N)
                continue;
            if (visitedBy[nx][ny] != -1) {
                if (not civilizations.isConnected(visitedBy[x][y],
                                                  visitedBy[nx][ny])) {
                    civilizations.unionParent(visitedBy[x][y],
                                              visitedBy[nx][ny]);
                    cnt--;
                }
            }
        }
    }

    int time = 0;

    while (cnt > 1) {
        queue<pair<int, int>> nxtQ;

        while (not q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nx = x + delta[k];
                int ny = y + delta[3 - k];

                if (nx <= 0 or nx > N or ny <= 0 or ny > N)
                    continue;
                if (visitedBy[nx][ny] != -1)
                    continue;

                visitedBy[nx][ny] = visitedBy[x][y];
                nxtQ.emplace(nx, ny);

                for (int l = 0; l < 4; l++) {
                    int nnx = nx + delta[l];
                    int nny = ny + delta[3 - l];

                    if (nnx <= 0 or nnx > N or nny <= 0 or nny > N)
                        continue;
                    if (visitedBy[nnx][nny] == -1)
                        continue;

                    if (not civilizations.isConnected(visitedBy[nx][ny], visitedBy[nnx][nny])) {
                        civilizations.unionParent(visitedBy[nx][ny], visitedBy[nnx][nny]);
                        cnt--;
                    }
                }
            }
        }

        swap(q, nxtQ);
        time++;
    }

    cout << time;

    return 0;
}