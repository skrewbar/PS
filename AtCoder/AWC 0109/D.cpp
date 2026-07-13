#include <bits/stdc++.h>
using namespace std;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

using ll = long long;

int B[101010], W[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C, K;
    cin >> N >> C >> K;

    for (int i = 1; i <= N; i++) cin >> B[i] >> W[i];

    vector<vector<vector<ll>>> dp(2, vector(C + 1, vector(K + 1, 0LL)));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= C; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i & 1][j][k] = dp[(i - 1) & 1][j][k];

                if (j - W[i] >= 0)
                    maximize(dp[i & 1][j][k], dp[(i - 1) & 1][j - W[i]][k] + B[i]);
                if (k and j - W[i] / 2 >= 0)
                    maximize(dp[i & 1][j][k],
                                dp[(i - 1) & 1][j - W[i] / 2][k - 1] + B[i]);
            }
        }
    }


    ll ans = 0;
    for (int j = 0; j <= C; j++) {
        for (int k = 0; k <= K; k++) {
            maximize(ans, dp[N & 1][j][k]);
        }
    }

    cout << ans;

    return 0;
}
