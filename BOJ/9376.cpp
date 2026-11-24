#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int delta[] = {1, -1, 0, 0};
constexpr int INF = 1e5;

void solve() {
    int h, w;
    cin >> h >> w;
    h += 2, w += 2;

    vector<string> jail(h);
    jail.push_back("");
    for (int i = 0; i < w; i++)
        jail[0].push_back('.');

    vector<pair<int, int>> prisoners;
    for (int i = 1; i < h - 1; i++) {
        jail[i].push_back('.');
        string line;
        cin >> line;
        jail[i].append(line);
        jail[i].push_back('.');

        for (int j = 0; j < w; j++) {
            if (jail[i][j] == '$')
                prisoners.emplace_back(i, j);
        }
    }
    jail.push_back(jail.front());

    auto getMinDoor = [&](const pair<int, int> &start) {
        vector<vector<int>> minDoor(h, vector<int>(w, INF));
        minDoor[start.first][start.second] = 0;

        deque<pair<int, int>> q;
        q.push_front(start);

        while (not q.empty()) {
            auto [i, j] = q.front();
            q.pop_front();

            for (int k = 0; k < 4; k++) {
                int ni = i + delta[k];
                int nj = j + delta[3 - k];

                if (ni < 0 or ni >= h or nj < 0 or nj >= w)
                    continue;
                if (jail[ni][nj] == '*' or minDoor[ni][nj] != INF)
                    continue;

                if (jail[ni][nj] == '#') {
                    minDoor[ni][nj] = minDoor[i][j] + 1;
                    q.emplace_back(ni, nj);
                } else {
                    minDoor[ni][nj] = minDoor[i][j];
                    q.emplace_front(ni, nj);
                }
            }
        }

        return minDoor;
    };

    vector<vector<int>> minDoor = getMinDoor(pair(0, 0));
    for (auto prisoner : prisoners) {
        vector<vector<int>> pMinDoor = getMinDoor(prisoner);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                minDoor[i][j] += pMinDoor[i][j];
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (jail[i][j] == '#')
                minDoor[i][j] -= 2;

            ans = min(ans, minDoor[i][j]);
        }
    }

    println("{}", ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}