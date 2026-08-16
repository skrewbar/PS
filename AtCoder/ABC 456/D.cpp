#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int N = S.size();
    S = "#" + S;

    vector<vector<ll>> dp(N + 1, vector<ll>(3));
    for (int i = 1; i <= N; i++) {
        int c = S[i] - 'a';
        dp[i][c]++;

        for (int j = 0; j < 3; j++) {
            dp[i][j] += dp[i - 1][j];
            if (j != c) dp[i][c] += dp[i - 1][j];
            dp[i][j] %= MOD;
        }
    }

    cout << (dp[N][0] + dp[N][1] + dp[N][2]) % MOD;

    return 0;
}
