#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

double red[111][111][111], yellow[111][111][111];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int r = 1; r <= 100; r++) {
        for (int y = 1; y <= 100; y++) {
            red[r][y][0] = 1;
        }
    }
    for (int y = 1; y <= 100; y++) {
        for (int b = 1; b <= 100; b++) {
            yellow[0][y][b] = 1;
        }
    }

    for (int r = 1; r <= 100; r++) {
        for (int y = 1; y <= 100; y++) {
            for (int b = 1; b <= 100; b++) {
                int totalCases = r * y + y * b + b * r;

                red[r][y][b] += red[r - 1][y][b] * b * r / totalCases;
                red[r][y][b] += red[r][y - 1][b] * r * y / totalCases;
                red[r][y][b] += red[r][y][b - 1] * y * b / totalCases;

                yellow[r][y][b] += yellow[r - 1][y][b] * b * r / totalCases;
                yellow[r][y][b] += yellow[r][y - 1][b] * r * y / totalCases;
                yellow[r][y][b] += yellow[r][y][b - 1] * y * b / totalCases;
            }
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int r, y, b;
        cin >> r >> y >> b;

        println("{} {} {}", red[r][y][b], yellow[r][y][b],
                1 - red[r][y][b] - yellow[r][y][b]);
    }

    return 0;
}