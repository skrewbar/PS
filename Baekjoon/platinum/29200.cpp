#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> diffs(n+3);
    vector<vector<ll>> dp(n+3, vector<ll>(5, 0));
    for (int i = 1; i <= n; i++) {
        cin >> diffs[i];
    }

    dp[1][1] = diffs[1];
    dp[2][2] = diffs[1] ^ diffs[2];
    dp[3][1] = (diffs[1] ^ diffs[2]) + diffs[3];
    dp[3][2] = diffs[1] + (diffs[2] ^ diffs[3]);
    dp[3][3] = (diffs[1] ^ diffs[2] ^ diffs[3]);

    for (int i = 4; i <= n; i++) {
        dp[i][1] = max({dp[i-1][2], dp[i-1][3], dp[i-1][4]}) + diffs[i];
        dp[i][2] = max({dp[i-2][1], dp[i-2][3], dp[i-2][4]}) + (diffs[i-1] ^ diffs[i]);
        dp[i][3] = max({dp[i-3][1], dp[i-3][2], dp[i-3][4]}) + (diffs[i-2] ^ diffs[i-1] ^ diffs[i]);
        dp[i][4] = max({dp[i-4][1], dp[i-4][2], dp[i-4][3]}) + (diffs[i-3] ^ diffs[i-2] ^ diffs[i-1] ^ diffs[i]);
    }

    cout << *max_element(dp[n].begin(), dp[n].end());
}