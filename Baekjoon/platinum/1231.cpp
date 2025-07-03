#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int maxMoney[15], cost[55][15], dp[55][500'200];
// maxMoney[i] : i번째 날에 쓸 수 있는 최대 돈
// cost[i][j] : i번째 주식의 j번째 날의 가격
// dp : maxMoney를 구하기 위한 배낭 문제 dp배열

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, d, m;
    cin >> c >> d >> m;

    for (int i = 1; i <= c; i++)
        for (int j = 1; j <= d; j++)
            cin >> cost[i][j];

    maxMoney[1] = m;
    for (int day = 1; day < d; day++) {
        fill(&dp[0][0], &dp[0][maxMoney[day] + 1], -1);
        dp[0][0] = 0;
        for (int i = 1; i <= c; i++) {
            for (int j = 0; j <= maxMoney[day]; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - cost[i][day] >= 0 and dp[i][j - cost[i][day]] != -1)
                    dp[i][j] = max(dp[i][j],
                                   dp[i][j - cost[i][day]] + cost[i][day + 1]);
            }
        }
        for (int j = 0; j <= maxMoney[day]; j++) {
            if (dp[c][j] == -1)
                continue;
            maxMoney[day + 1] =
                max(maxMoney[day + 1], dp[c][j] + maxMoney[day] - j);
        }
    }

    print("{}", maxMoney[d]);

    return 0;
}