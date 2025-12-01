#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int DOWN = 0, RIGHT = 1;

int dir[1010][1010];
int cnt[1010][1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, N;
    cin >> H >> W >> N;

    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            cin >> dir[i][j];
        }
    }

    cnt[1][1] = N - 1;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            cnt[i][j + 1] +=
                cnt[i][j] / 2 + (cnt[i][j] & 1 and dir[i][j] == RIGHT);
            cnt[i + 1][j] +=
                cnt[i][j] / 2 + (cnt[i][j] & 1 and dir[i][j] == DOWN);
        }
    }

    int i = 1, j = 1;
    while (i <= H and j <= W) {
        dir[i][j] = (dir[i][j] + cnt[i][j]) & 1;

        if (dir[i][j] == RIGHT)
            j++;
        else
            i++;
    }

    cout << i << ' ' << j;

    return 0;
}