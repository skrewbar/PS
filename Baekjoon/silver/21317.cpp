#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}


int main() {
    fastio();

    int n, k;
    cin >> n;

    int smallEnergy[n-1];
    int bigEnergy[n-1];

    for (int i = 0; i < n-1; i++) {
        cin >> smallEnergy[i];
        cin >> bigEnergy[i];
    }

    cin >> k;
    int dp[n][2];
    fill(&dp[0][0], &dp[n-1][2], 1e9);

    dp[0][0] = 0;
    if (n >= 2) dp[1][0] = smallEnergy[0];
    if (n >= 3) dp[2][0] = min(dp[1][0] + smallEnergy[1], bigEnergy[0]);

    for (int i = 3; i < n; i++) {
        dp[i][0] = min(dp[i-1][0] + smallEnergy[i-1], dp[i-2][0] + bigEnergy[i-2]);
        dp[i][1] = min({dp[i-1][1] + smallEnergy[i-1], dp[i-2][1] + bigEnergy[i-2], dp[i-3][0] + k});
    }


    cout << min(dp[n-1][0], dp[n-1][1]);

    return 0;
}