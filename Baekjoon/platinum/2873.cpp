#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

pair<int, int>& operator+=(pair<int, int>& p1, const pair<int, int>& p2) {
    p1.first += p2.first, p1.second += p2.second;
    return p1;
}

int grid[1010][1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;

    if (r & 1 or c & 1) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c - 1; j++)
                print("{}", (i & 1 ? 'L' : 'R'));
            if (i + 1 < r)
                print("D");
        }
        return 0;
    }

    pair<int, int> exclude(0, 1);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
            if ((i + j) & 1 and
                grid[i][j] < grid[exclude.first][exclude.second])
                exclude = pair(i, j);
        }
    }

    int limitRow = exclude.first & ~1;
    pair<int, int> coord(0, 0);
    auto& [row, col] = coord;
    for (row = 0; row < limitRow; row++) {
        for (int j = 0; j < c - 1; j++)
            print("{}", (row & 1 ? 'L' : 'R'));
        print("D");
    }

    for (; col < exclude.second; col++) {
        if (limitRow == row) {
            print("DR");
            row++;
        } else {
            print("UR");
            row--;
        }
    }
    for (; col + 1 < c; col++) {
        if (limitRow == row) {
            print("RD");
            row++;
        } else {
            print("RU");
            row--;
        }
    }

    for (; row + 1 < r; row++) {
        print("D");
        for (int j = 0; j < c - 1; j++)
            print("{}", (row & 1 ? 'L' : 'R'));
    }

    return 0;
}