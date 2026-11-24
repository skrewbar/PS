#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

bool dp[55][1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;

    dp[2][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= s; j++) {
            if (not dp[i][j])
                continue;
            for (int k = 1; i + k <= n; k++) {
                int pathCnt = j + (k + 1) * k / 2;
                if (pathCnt <= s)
                    dp[i + k][j + (k + 1) * k / 2] = true;
            }
        }
    }
    print("{}", dp[n][s] ? 1 : 0);

    return 0;
}