#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

int maxJewel[111][111];
bool dp[1 << 15][15];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, K;
    cin >> n >> m >> K;

    vector<int> jewel(K);
    for (int i = 0; i < K; i++)
        cin >> jewel[i];

    fill(&maxJewel[0][0], &maxJewel[n][n + 1], -INF);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        maxJewel[a][b] = maxJewel[b][a] = c;
    }

    for (int i = 1; i <= n; i++)
        maxJewel[i][i] = INF;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                maxJewel[i][j] = max(maxJewel[i][j], min(maxJewel[i][k], maxJewel[k][j]));
            }
        }
    }

    for (int i = 0; i < K; i++)
        dp[1 << i][i] = (maxJewel[1][jewel[i]] >= 0);

    int answer = 0;
    for (int bit = 1; bit < (1 << K); bit++) {
        int jewelCnt = 0;
        for (int i = 0; i < K; i++) {
            if (bit & (1 << i))
                jewelCnt++;
        }

        for (int i = 0; i < K; i++) {
            if (not dp[bit][i])
                continue;

            if (maxJewel[jewel[i]][1] >= jewelCnt)
                answer = max(answer, jewelCnt);

            for (int j = 0; j < K; j++) {
                if (bit & (1 << j))
                    continue;

                if (maxJewel[jewel[i]][jewel[j]] < jewelCnt)
                    continue;

                int nxtBit = bit | (1 << j);
                dp[nxtBit][j] = true;
            }
        }
    }

    println("{}", answer);

    return 0;
}