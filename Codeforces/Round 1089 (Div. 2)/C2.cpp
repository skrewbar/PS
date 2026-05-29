#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll primes[] = {1,  2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
               31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
constexpr int primeCnt = 21;

ll a[50505], b[50505];
int dp[50505][21];
bool shrinked[50505];

void solve() {
    int n;
    cin >> n;

    fill(shrinked, shrinked + n + 5, false);

    a[0] = a[n + 1] = 1;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        ll lg = gcd(a[i - 1], a[i]);
        ll rg = gcd(a[i], a[i + 1]);

        ll lbound = lg * rg / gcd(lg, rg);

        if (lbound < a[i] and lbound <= b[i]) {
            answer++;
            shrinked[i] = true;
            a[i] = lbound;
        }
    }

    for (int i = 1; i <= n; i++) {
        fill(dp[i], dp[i] + primeCnt, 0);

        for (int pk = 0; pk < primeCnt; pk++)
            dp[i][0] = max(dp[i][0], dp[i - 1][pk]);

        if (shrinked[i]) continue;

        ll lg = gcd(a[i - 1], a[i]);
        ll rg = gcd(a[i], a[i + 1]);

        for (int k = 1; k < primeCnt; k++) {
            if (a[i] * primes[k] > b[i]) continue;

            for (int pk = 0; pk < primeCnt; pk++) {
                if (lg != gcd(a[i - 1] * primes[pk], a[i] * primes[k]))
                    continue;
                if (rg != gcd(a[i] * primes[k], a[i + 1])) continue;

                dp[i][k] = max(dp[i][k], dp[i - 1][pk] + 1);
            }
        }
    }

    int maxDp = 0;
    for (int k = 0; k < primeCnt; k++) maxDp = max(maxDp, dp[n][k]);

    cout << answer + maxDp << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
