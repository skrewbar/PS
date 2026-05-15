#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

int a[101010], nxt[101010];
int dp[400][400][400];
int preMax[400][400];

void solve() {
    int n, k;
    cin >> n >> k;

    fill(&dp[0][0][0], &dp[k + 5][0][0], 0);
    fill(&preMax[0][0], &preMax[k + 5][0], 0);

    int last = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        minimize(a[i], k);

        if (a[i] <= a[last])
            continue;
        nxt[last] = i;
        last = i;
    }
    nxt[last] = n + 1;

    int answer = 0;
    for (int i = nxt[0], cnt = 1; i <= n; i = nxt[i], cnt++) {
        for (int sum = 1; sum <= k; sum++) {
            for (int m = 1; m <= min(sum, a[i]); m++) {
                dp[cnt][sum][m] =
                    max(dp[cnt - 1][sum][m], preMax[cnt - 1][sum - m])
                    + m * (nxt[i] - i);
                maximize(answer, dp[cnt][sum][m]);
            }
        }

        for (int sum = 1; sum <= k; sum++) {
            preMax[cnt][sum] = 0;
            for (int m = 1; m <= a[i]; m++) {
                maximize(preMax[cnt][sum], dp[cnt][sum][m]);
            }
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}