#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

bool isIncreasing(const string& num) {
    for (int i = 1; i < (int)num.size(); i++)
        if (num[i - 1] > num[i])
            return false;

    return true;
}

// dp[i][j] represents the counts of increasing number which starts with j and its length is i
ll dp[100][10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(dp[1], dp[1] + 10, 1);
    for (int i = 1; i <= 80; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = j; k <= 9; k++)
                dp[i][j] += dp[i - 1][k];
        }
    }

    int T;
    cin >> T;
    while (T--) {
        string num;
        cin >> num;

        if (not isIncreasing(num)) {
            cout << -1 << '\n';
            continue;
        }

        ll ans = 0;
        for (int k = 0; k < num[0] - '0'; k++)
            ans += dp[num.size()][k];

        for (int i = 1; i < (int)num.size(); i++) {
            for (int k = num[i - 1] - '0'; k < num[i] - '0'; k++)
                ans += dp[num.size() - i][k];
        }

        cout << ans << '\n';
    }

    return 0;
}