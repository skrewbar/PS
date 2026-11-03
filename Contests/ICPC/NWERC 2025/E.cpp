#include <bits/stdc++.h>
using namespace std;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

double dp[111][111][111];

double getDp(int i, int j, int k) {
    if (dp[i][j][k] >= 0) return dp[i][j][k];
    dp[i][j][k] = INFINITY;

    if (i == 0) return dp[i][j][k] = min(j, k) * 3;

    minimize(dp[i][j][k], getDp(i - 1, j + 1, k) + 3);
    minimize(dp[i][j][k], getDp(i - 1, j, k + 1) + 3);
    minimize(dp[i][j][k],
             (getDp(i - 1, j + 1, k) + getDp(i - 1, j, k + 1)) / 2 + 1.5);

    return dp[i][j][k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    fill(&dp[0][0][0], &dp[n][n][n + 5], -1);

    string s;
    cin >> s;

    map<char, int> cnt;
    for (char c : s) cnt[c]++;

    vector<int> counts = {cnt['r'], cnt['g'], cnt['b']};
    sort(counts.begin(), counts.end());

    cout << fixed;
    cout.precision(10);
    cout << getDp(counts[0], counts[1], counts[2]);

    return 0;
}
