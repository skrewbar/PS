#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

void solve() {
    int H, W, O, F;
    pair<int, int> s, e;
    cin >> H >> W >> O >> F >> s.first >> s.second >> e.first >> e.second;

    vector<vector<int>> power(H + 1, vector<int>(W + 1, -1));
    vector<vector<int>> height(H + 1, vector<int>(W + 1, 0));
    while (O--) {
        int X, Y, L;
        cin >> X >> Y >> L;
        height[X][Y] = L;
    }

    queue<pair<int, int>> q;
    q.push(s);
    power[s.first][s.second] = F;
    while (not q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (power[x][y] == 0)
            continue;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (!(1 <= nx and nx <= H) or !(1 <= ny and ny <= W))
                continue;

            if (power[nx][ny] == -1 and
                height[nx][ny] - height[x][y] <= power[x][y]) {
                power[nx][ny] = power[x][y] - 1;
                q.emplace(nx, ny);
            }
        }
    }

    cout << (power[e.first][e.second] != -1 ? "잘했어!!" : "인성 문제있어??")
         << '\n';
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