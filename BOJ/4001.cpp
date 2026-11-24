#include <bits/stdc++.h>
using namespace std;

int dr[] = {0, -1, -1, -1, 0, 1, 1, 1}, dc[] = {1, 1, 0, -1, -1, -1, 0, 1};

int w, h;

bool isInvalid(int row, int col) {
    return row < 1 or col < 1 or row > h or col > w;
}

constexpr int MX = 1515;
char labyrinth[MX][MX];
int ld[MX][MX], ru[MX][MX], obstacle[MX][MX];

void build(int arr[MX][MX], int r, int c) {
    if (r)
        arr[r][c] += arr[r - 1][c];
    if (c)
        arr[r][c] += arr[r][c - 1];
    if (r and c)
        arr[r][c] -= arr[r - 1][c - 1];
}

int getCount(int arr[MX][MX], int r1, int r2, int c1, int c2) {
    int ret = arr[r2][c2];

    if (r1 > 0)
        ret -= arr[r1 - 1][c2];
    if (c1 > 0)
        ret -= arr[r2][c1 - 1];
    if (r1 > 0 and c1 > 0)
        ret += arr[r1 - 1][c1 - 1];

    return ret;
}

void obstacleBfs(pair<int, int> start, int arr[MX][MX]) {
    queue<pair<int, int>> q;
    auto [r, c] = start;
    arr[r][c] = 1;
    q.push(start);

    while (not q.empty()) {
        tie(r, c) = q.front();
        q.pop();

        for (int k = 0; k < 8; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (isInvalid(nr, nc) or arr[nr][nc] == 1 or
                labyrinth[nr][nc] != '#')
                continue;

            arr[nr][nc] = 1;
            q.emplace(nr, nc);
        }
    }
}

int getMinBlockableSize(int row, int col) {
    int maxSize = min(h - row + 1, w - col + 1);
    if (row + maxSize - 1 == h and col + maxSize - 1 == w)
        maxSize--;

    int lo = 1, hi = maxSize + 1;

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (getCount(ld, row - 1, row + mid, col - 1, col + mid) > 0 and
            getCount(ru, row - 1, row + mid, col - 1, col + mid) > 0)
            hi = mid;
        else
            lo = mid + 1;
    }

    return lo <= maxSize ? lo : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> h;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> labyrinth[i][j];
            obstacle[i][j] = (labyrinth[i][j] == '#');
        }
    }

    for (int r = 1; r <= h; r++) {
        ld[r][0] = ru[r][w + 1] = 1;

        if (labyrinth[r][1] == '#')
            obstacleBfs({r, 1}, ld);
        if (labyrinth[r][w] == '#')
            obstacleBfs({r, w}, ru);
    }
    for (int c = 1; c <= w; c++) {
        ld[h + 1][c] = ru[0][c] = 1;

        if (labyrinth[h][c] == '#')
            obstacleBfs({h, c}, ld);
        if (labyrinth[1][c] == '#')
            obstacleBfs({1, c}, ru);
    }

    for (int r = 0; r <= h + 1; r++) {
        for (int c = 0; c <= w + 1; c++) {
            build(ld, r, c);
            build(ru, r, c);
            build(obstacle, r, c);
        }
    }

    int l = MX, x, y;

    for (int r = 1; r <= h; r++) {
        for (int c = 1; c <= w; c++) {
            if (r == 1 and c == 1)
                continue;
            if (r == h and c == w)
                continue;
            if (labyrinth[r][c] == '#')
                continue;

            int sz = getMinBlockableSize(r, c);
            if (sz == -1 or
                getCount(obstacle, r, r + sz - 1, c, c + sz - 1) > 0)
                continue;

            if (sz < l) {
                l = sz;
                x = r, y = c;
            }
        }
    }

    if (l == MX)
        cout << "Impossible";
    else
        cout << l << ' ' << y << ' ' << x;

    return 0;
}