#include <bits/stdc++.h>
using namespace std;


int n, w;
vector<vector<int>> enemies;
vector<vector<int>> dp;


void solve(int start) {
    for (int i = start; i <= n; i++) {
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + 1;
        if (enemies[i-1][1] + enemies[i-1][2] <= w) {
            dp[i][0] = min(dp[i][0], dp[i-1][0] + 1);
        }
        if (enemies[i-2][1] + enemies[i-1][1] <= w and enemies[i-2][2] + enemies[i-1][2] <= w) {
            dp[i][0] = min(dp[i][0], dp[i-2][0] + 2);
        }

        dp[i][1] = dp[i][2] = dp[i][0] + 1;
        if (enemies[i-1][1] + enemies[i][1] <= w) {
            dp[i][1] = min(dp[i][1], dp[i-1][2] + 1);
        }
        if (enemies[i-1][2] + enemies[i][2] <= w) {
            dp[i][2] = min(dp[i][2], dp[i-1][1] + 1);
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> w;
        enemies = vector(n+1, vector<int>(3));
        for (int i = 1; i <= n; i++) cin >> enemies[i][1];
        for (int i = 1; i <= n; i++) cin >> enemies[i][2];

        if (n == 1) {
            cout << (enemies[1][1] + enemies[1][2] <= w ? 1 : 2) << '\n';
            continue;
        }

        dp = vector(n+1, vector<int>(3));
        dp[1][1] = dp[1][2] = 1;
        solve(2);

        int answer = min(dp[n][1], dp[n][2]) + 1;
        if (enemies[n][1] + enemies[n][2] <= w) {
            answer = min(answer, dp[n][0] + 1);
        }
        if (enemies[n-1][1] + enemies[n][1] <= w and enemies[n-1][2] + enemies[n][2] <= w) {
            answer = min(answer, dp[n-1][0] + 2);
        }

        if (enemies[n][1] + enemies[1][1] <= w) {
            // => (n, 1) + (1, 1) 한 소대로 커버
            dp[2][0] = 1;
            dp[2][1] = 2;
            dp[2][2] = (enemies[1][2] + enemies[2][2] <= w ? 1 : 2);
            solve(3);
            answer = min(answer, dp[n][2] + 1);
        }
        if (enemies[n][2] + enemies[1][2] <= w) {
            // => (n, 2) + (1, 2) 한 소대로 커버
            dp[2][0] = 1;
            dp[2][1] = (enemies[1][1] + enemies[2][1] <= w ? 1 : 2);
            dp[2][2] = 2;
            solve(3);
            answer = min(answer, dp[n][1] + 1);
        }
        if (enemies[n][1] + enemies[1][1] <= w and enemies[n][2] + enemies[1][2] <= w) {
            // => ((n, 1) + (1, 1)) + ((n, 2) + (1, 2)) 두 소대로 커버
            dp[2][0] = 0;
            dp[2][1] = dp[2][2] = 1;
            solve(3);
            answer = min(answer, dp[n][0] + 2);
        }

        cout << answer << '\n';
    }
}