#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};

int minTime[1010][1010], seonuTime[1010][1010];
string grid[1010];

int N, M;

int rendezvousTime(int r, int c) {
    if (r != 0 and r != N - 1 and c != 0 and c != M - 1)
        return -1;
    if (seonuTime[r][c] % 2 != minTime[r][c] % 2)
        return -1;

    int ret = seonuTime[r][c];
    while (ret < minTime[r][c])
        ret += 2 * (N + M - 2);

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    pair<int, int> sanghyuck, seonu;

    for (int i = 0; i < N; i++) {
        cin >> grid[i];

        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'A')
                sanghyuck = {i, j};
            else if (grid[i][j] == 'B')
                seonu = {i, j};
        }
    }

    fill(&seonuTime[0][0], &seonuTime[N][M], -1);
    auto [r, c] = seonu;
    int time = 0;
    while (seonuTime[r][c] == -1) {
        while (seonuTime[r][c] == -1 and r == 0 and c < M - 1)
            seonuTime[r][c++] = time++;
        while (seonuTime[r][c] == -1 and c == M - 1 and r < N - 1)
            seonuTime[r++][c] = time++;
        while (seonuTime[r][c] == -1 and r == N - 1 and c > 0)
            seonuTime[r][c--] = time++;
        while (seonuTime[r][c] == -1 and c == 0 and r > 0)
            seonuTime[r--][c] = time++;
    }

    fill(&minTime[0][0], &minTime[N][M], -1);
    tie(r, c) = sanghyuck;
    minTime[r][c] = 0;
    queue<pair<int, int>> q;
    q.emplace(sanghyuck);

    int answer = INF;

    while (not q.empty()) {
        tie(r, c) = q.front();
        q.pop();

        int t = rendezvousTime(r, c);
        if (t != -1)
            answer = min(answer, t);

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr < 0 or nc < 0 or nr >= N or nc >= M)
                continue;
            if (minTime[nr][nc] != -1 or grid[nr][nc] == 'G')
                continue;

            minTime[nr][nc] = minTime[r][c] + 1;
            q.emplace(nr, nc);
        }
    }

    cout << (answer != INF ? answer : -1);

    return 0;
}