#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

double prob[20][20];
double dp[2][1 << 20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> prob[i][j];
            prob[i][j] /= 100;
        }
    }

    fill(&dp[0][0], &dp[1][1 << N], 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1 << N); j++) {
            int completed = 0;
            for (int k = 0; k < N; k++) {
                if (j & (1 << k))
                    completed++;
            }
            if (completed != i + 1)
                continue;

            dp[i & 1][j] = 0;

            for (int k = 0; k < N; k++) {
                if (~j & (1 << k))
                    continue;

                dp[i & 1][j] =
                    max(dp[i & 1][j], dp[~i & 1][j ^ (1 << k)] * prob[i][k]);
            }
        }
    }

    cout << dp[~N & 1][(1 << N) - 1] * 100;

    return 0;
}