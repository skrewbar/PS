#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int rect[2525][2525], diam[2525][2525];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w, h, k;
    cin >> w >> h >> k;

    while (k--) {
        int type;
        cin >> type;

        if (type == 1) {
            int px, py, qx, qy;
            cin >> px >> py >> qx >> qy;
            px++, py++, qx++, qy++;
            rect[py][px]++, rect[py][qx + 1]--;
            rect[qy + 1][px]--, rect[qy + 1][qx + 1]++;
        } else {
            int px, py, r;
            cin >> px >> py >> r;
            px++, py++;
            diam[py + 1 - r][px]++, diam[py + 1 - (r + 1)][px]++;
            diam[py + 1 + r][px]++, diam[py + 1 + r + 1][px]++;

            diam[py + 1][px - r]--, diam[py + 1][px - r - 1]--;
            diam[py + 1][px + r]--, diam[py + 1][px + r + 1]--;
        }
    }

    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            rect[i][j] += rect[i][j - 1];

    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            rect[i][j] += rect[i - 1][j];
    
    for (int i = 1; i <= h; i++)
        for (int j = 0; j <= w; j++)
            diam[i][j] += diam[i - 1][j + 1];
    
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            diam[i][j] += diam[i - 1][j - 1];

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            print("{}", (rect[i][j] + diam[i][j]) & 1 ? '#' : '.');
        }
        print("\n");
    }

    return 0;
}