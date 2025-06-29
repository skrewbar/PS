#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int di[] = {-1, 0, 1, -1, 0, 1}, dj[] = {1, 1, 1, -1, -1, -1};

int n, m;
vector<string> classRoom;

struct Grid {
    int i, j, num;

    Grid(int i, int j) : i(i), j(j), num(i * m + j) {}

    bool isValid() {
        return 0 <= i and i < n and 0 <= j and j < m and classRoom[i][j] == '.';
    }
};

vector<vector<int>> matchList;
vector<bool> matched;
vector<int> matching;

bool match(int grid) {
    for (int adj : matchList[grid]) {
        if (matched[adj])
            continue;
        matched[adj] = true;
        if (matching[adj] == -1 or match(matching[adj])) {
            matching[adj] = grid;
            return true;
        }
    }

    return false;
}

void solve() {
    cin >> n >> m;

    classRoom = vector<string>(n);
    matchList = vector(n * m, vector<int>());
    matched = vector(n * m, false);
    matching = vector(n * m, -1);

    int seatCnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> classRoom[i];
        for (int j = 0; j < m; j++)
            seatCnt += (classRoom[i][j] == '.');
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j += 2) {
            Grid now(i, j);
            if (not now.isValid())
                continue;
            for (int k = 0; k < 6; k++) {
                Grid adj(i + di[k], j + dj[k]);
                if (adj.isValid())
                    matchList[now.num].push_back(adj.num);
            }
        }
    }

    int maxMatching = 0;
    for (int i = 0; i < n * m; i++) {
        fill(matched.begin(), matched.end(), false);
        maxMatching += match(i);
    }

    print("{}\n", seatCnt - maxMatching);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c;
    cin >> c;
    while (c--)
        solve();
    return 0;
}