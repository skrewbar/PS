#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll A[111], B[11];
ll dp[111][1 << 11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < M; i++)
        cin >> B[i];

    dp[0][0] = A[0];
    for (int decor = 0; decor < M; decor++)
        dp[0][1 << decor] = A[0] * B[decor];

    for (int i = 1; i < N; i++) {
        for (int decors = 0; decors < 1 << M; decors++) {
            dp[i][decors] = dp[i - 1][decors] + A[i];

            for (int decor = 0; decor < M; decor++) {
                if (~decors & (1 << decor))
                    continue;

                ll sum = A[i];
                for (int j = i - 1; j >= max(0, i - K); j--) {
                    dp[i][decors] =
                        max(dp[i][decors],
                            dp[j][decors ^ (1 << decor)] + sum * B[decor]);

                    sum += A[j];
                }

                if (i < K)
                    dp[i][decors] = max(dp[i][decors], sum * B[decor]);
            }
        }
    }

    ll ans = 0;
    for (int decors = 0; decors < 1 << M; decors++)
        ans = max(ans, dp[N - 1][decors]);

    cout << ans;

    return 0;
}