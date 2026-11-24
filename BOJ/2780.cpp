#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp[10][1001];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        fill(&dp[0][0], &dp[9][1001], 0);
        for (int i = 0 ; i <= 9 ; i++) {
            dp[i][1] = 1;
        }

        for (int count = 2 ; count <= n ; count++) {
            dp[0][count] = dp[7][count-1];
            dp[1][count] = dp[2][count-1] + dp[4][count-1];
            dp[2][count] = dp[1][count-1] + dp[3][count-1] + dp[5][count-1];
            dp[3][count] = dp[2][count-1] + dp[6][count-1];
            dp[4][count] = dp[1][count-1] + dp[5][count-1] + dp[7][count-1];
            dp[5][count] = dp[2][count-1] + dp[4][count-1] + dp[6][count-1] + dp[8][count-1];
            dp[6][count] = dp[3][count-1] + dp[5][count-1] + dp[9][count-1];
            dp[7][count] = dp[4][count-1] + dp[8][count-1] + dp[0][count-1];
            dp[8][count] = dp[5][count-1] + dp[7][count-1] + dp[9][count-1];
            dp[9][count] = dp[6][count-1] + dp[8][count-1];

            for (int i = 0 ; i <= 9 ; i++) {
                dp[i][count] %= 1234567;
            }
        }

        int ans = 0;
        for (int i = 0 ; i <= 9 ; i++) {
            ans += dp[i][n];
        }

        cout << ans % 1234567 << '\n';
    }

    return 0;
}