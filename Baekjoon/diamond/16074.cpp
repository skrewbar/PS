#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct DisjointSet {
    vector<int> parent;

    DisjointSet(size_t size) : parent(size) {
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int findParent(int x) {
        if (parent[x] != x)
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);

        if (u != v)
            parent[u] = v;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};

int m, n;

int coordToNum(int r, int c) {
    return r * n + c;
}
pair<int, int> numToCoord(int x) {
    int r = x / n;
    return pair(r, x % r);
}

int height[555][555];

int depart[101010], dest[101010], lo[101010], hi[101010], ans[101010];
queue<int> queries[252525];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> m >> n >> q;

    vector<int> heightValues;
    heightValues.reserve(m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> height[i][j];
            heightValues.push_back(height[i][j]);
        }
    }

    sort(heightValues.begin(), heightValues.end());
    heightValues.erase(
        unique(heightValues.begin(), heightValues.end()),
        heightValues.end()
    );

    for (int i = 0; i < q; i++) {
        int x, y;

        cin >> x >> y;
        depart[i] = coordToNum(x - 1, y - 1);

        cin >> x >> y;
        dest[i] = coordToNum(x - 1, y - 1);

        if (depart[i] == dest[i]) {
            ans[i] = height[x - 1][y - 1];
        } else {
            lo[i] = 0, hi[i] = heightValues.size() - 1;
            queries[(lo[i] + hi[i]) / 2].push(i);
        }
    }

    vector<pair<int, int>> sortedCells;
    sortedCells.reserve(m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sortedCells.emplace_back(i, j);
        }
    }
    sort(sortedCells.begin(), sortedCells.end(), [&](auto a, auto b) {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        return height[x1][y1] < height[x2][y2];
    });

    while (true) {
        bool solved = true;
        for (int i = 0; i < heightValues.size(); i++) {
            if (not queries[i].empty()) {
                solved = false;
                break;
            }
        }

        if (solved)
            break;

        DisjointSet disjointSet(m * n);

        int i = 0;
        for (int mid = 0; mid < heightValues.size(); mid++) {
            for (;i < sortedCells.size(); i++) {
                auto [x, y] = sortedCells[i];
                if (height[x][y] > heightValues[mid])
                    break;

                int delta[] = {1, -1, 0, 0};
                for (int k = 0; k < 4; k++) {
                    int nx = x + delta[k];
                    int ny = y + delta[3 - k];

                    if (nx < 0 or nx >= m or ny < 0 or ny >= n)
                        continue;
                    if (height[nx][ny] > height[x][y])
                        continue;

                    disjointSet.unionParent(
                        coordToNum(x, y),
                        coordToNum(nx, ny)
                    );
                }
            }

            while (not queries[mid].empty()) {
                int queryNum = queries[mid].front();
                queries[mid].pop();

                if (disjointSet.isConnected(
                    depart[queryNum],
                    dest[queryNum]
                ))
                    hi[queryNum] = mid;
                else
                    lo[queryNum] = mid + 1;

                if (lo[queryNum] == hi[queryNum]) {
                    ans[queryNum] = heightValues[lo[queryNum]];
                } else {
                    int newMid = (lo[queryNum] + hi[queryNum]) / 2;
                    queries[newMid].push(queryNum);
                }
            }
        }
    }

    for (int i = 0; i < q; i++)
        println("{}", ans[i]);

    return 0;
}