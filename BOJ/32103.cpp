#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

bool isStaff[202020][4];
bool turnOn[202020][4];
int dp[2][1 << 9];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int staffTurnOnCnt = 0;

    while (M--) {
        int x, y, t;
        cin >> x >> y >> t;

        isStaff[y][x] = true;

        if (t == 1) {
            turnOn[y][x] = true;
            staffTurnOnCnt++;
        }
    }

    fill(&dp[0][0], &dp[1][1 << 9], INF);
    dp[1][0] = 0;

    for (int i = 1; i <= N; i++) {
        fill(&dp[(i + 1) & 1][0], &dp[(i + 1) & 1][1 << 9], INF);
        for (int j = 0; j < (1 << 9); j++) {
            if (dp[i & 1][j] == INF)
                continue;

            if ((j & 0b111) == 0b111) {
                dp[(i + 1) & 1][j >> 3] = min(dp[(i + 1) & 1][j >> 3], dp[i & 1][j]);
                continue;
            }

            int nxt = j | 0b1011;
            if (not isStaff[i][1] or turnOn[i][1])
                dp[i & 1][nxt] = min(dp[i & 1][nxt], dp[i & 1][j] + not turnOn[i][1]);

            nxt = j | 0b100110;
            if (not isStaff[i][3] or turnOn[i][3])
                dp[i & 1][nxt] = min(dp[i & 1][nxt], dp[i & 1][j] + not turnOn[i][3]);

            if (i + 1 <= N) {
                nxt = j | 0b1011001;
                if (not isStaff[i + 1][1] or turnOn[i + 1][1])
                    dp[i & 1][nxt] =
                        min(dp[i & 1][nxt], dp[i & 1][j] + not turnOn[i + 1][1]);

                nxt = j | 0b100110100;
                if (not isStaff[i + 1][3] or turnOn[i + 1][3])
                    dp[i & 1][nxt] =
                        min(dp[i & 1][nxt], dp[i & 1][j] + not turnOn[i + 1][3]);
            }
        }
    }

    int ans = INF;
    for (int j = 0; j < (1 << 9); j++)
        ans = min(ans, dp[(N + 1) & 1][j]);

    if (ans == INF)
        println("-1");
    else
        println("{}", ans + staffTurnOnCnt);

    return 0;
}