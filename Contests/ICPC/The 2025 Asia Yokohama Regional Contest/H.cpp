#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<string> grid(n + k + 1, string(m + k + 1, '.'));
    vector<pair<int, int>> sharps;

    for (int i = 1; i <= n; i++) {
        cin >> grid[i];
        grid[i] = '#' + grid[i];
        grid[i].resize(m + k + 1, '#');

        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '#') sharps.emplace_back(i, j);
        }
    }
    sort(all(sharps));

    auto remove = [&](int r, int c) {
        if (grid[r][c] == '.') return true;

        int rs, re, cs, ce;

        bitset<4> dir;

        for (int j = c + 1; j < c + k - 1; j++) {
            if (grid[r][j] == '.') {
                dir[0] = true;
                rs = re = r;
                cs = c + 1;
                ce = c + k - 2;
            }
            if (r + k - 1 <= n and grid[r + k - 1][j] == '.') {
                dir[1] = true;
                rs = re = r + k - 1;
                cs = c + 1;
                ce = c + k - 2;
            }
        }
        for (int i = r + 1; i < r + k - 1; i++) {
            if (grid[i][c] == '.') {
                dir[2] = true;
                rs = r + 1;
                re = r + k - 2;
                cs = ce = c;
            }
            if (c + k - 1 <= m and grid[i][c + k - 1] == '.') {
                dir[3] = true;
                rs = r + 1;
                re = r + k - 2;
                cs = ce = c + k - 1;
            }
        }

        if (dir.count() != 1) return false;

        for (int i : {r, r + k - 1}) {
            for (int j = c + 1; j < c + k - 1; j++) {
                if (rs <= i and i <= re and cs <= j and j <= ce) continue;

                if (grid[i][j] != '#') return false;
                grid[i][j] = '.';
            }
        }
        for (int i = r + 1; i < r + k - 1; i++) {
            for (int j : {c, c + k - 1}) {
                if (rs <= i and i <= re and cs <= j and j <= ce) continue;

                if (grid[i][j] != '#') return false;
                grid[i][j] = '.';
            }
        }
        for (int i : {r, r + k - 1}) {
            for (int j : {c, c + k - 1}) {
                if (rs <= i and i <= re and cs <= j and j <= ce) continue;

                if (grid[i][j] != '#') return false;
                grid[i][j] = '.';
            }
        }

        return true;
    };

    for (auto [r, c] : sharps) {

        if (not remove(r, c)) {
            cout << "no\n";
            return;
        }
    }

    cout << "yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
