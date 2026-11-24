#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int MAX_N = 202020, MAX_B = 333, MOD = 1e9 + 7;

int B[MAX_N], dp[MAX_B][MAX_B], cnt[MAX_B], pairCnt[MAX_B][MAX_B];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> B[i];

    for (int i = 1; i <= N; i++) {
        int z = B[i];
        for (int y = 0; y < MAX_B; y++) {
            int x = y + B[i];

            if (x >= MAX_B)
                continue;

            dp[y][z] += (dp[x][y] + pairCnt[x][y]) % MOD;
            dp[y][z] %= MOD;
        }

        for (int B_j = 0; B_j < MAX_B; B_j++) {
            pairCnt[B_j][z] += cnt[B_j];
            pairCnt[B_j][z] %= MOD;
        }
        cnt[B[i]]++;
    }

    int answer = 0;
    for (int x = 0; x < MAX_B; x++) {
        for (int y = 0; y < MAX_B; y++) {
            answer += dp[x][y];
            answer %= MOD;
        }
    }

    cout << answer;

    return 0;
}