#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int pos[3030], posSum[3030], dp[3030];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> pos[i];
    sort(pos + 1, pos + N + 1);
    for (int i = 1; i <= N; i++)
        posSum[i] = posSum[i - 1] + pos[i];

    int t, h;
    cin >> t >> h;

    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i - 1] + pos[i] * t;
        for (int j = i; j >= 1; j--) {
            int mid = (i + j) >> 1;

            int cost = h;
            cost +=
                (pos[mid] * (mid - j + 1) - (posSum[mid] - posSum[j - 1])) * t;
            cost +=
                ((posSum[i] - posSum[mid - 1]) - pos[mid] * (i - mid + 1)) * t;

            dp[i] = min(dp[i], dp[j - 1] + cost);
        }
    }

    cout << dp[N];

    return 0;
}