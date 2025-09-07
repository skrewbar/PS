#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

vector<int> negX = {0}, posX = {0};
int n, m;

int dp[333][333][2];

int getMaxCandy(int basketCnt) {
    fill(&dp[0][0][0], &dp[basketCnt][basketCnt][2], INF);
    dp[0][0][0] = dp[0][0][1] = 0;

    for (int i = 0; i <= min(basketCnt, (int)negX.size() - 1); i++) {
        for (int j = 0; j <= min(basketCnt, (int)posX.size() - 1); j++) {
            int meltingCnt = basketCnt - (i + j);

            for (int flag = 0; flag < 2; flag++) {
                int now = flag ? posX[j] : negX[i];

                if (i + 1 <= min(basketCnt, (int)negX.size() - 1))
                    dp[i + 1][j][0] = min(
                        dp[i + 1][j][0],
                        dp[i][j][flag] + meltingCnt * abs(now - negX[i + 1]));

                if (j + 1 <= min(basketCnt, (int)posX.size() - 1))
                    dp[i][j + 1][1] = min(
                        dp[i][j + 1][1],
                        dp[i][j][flag] + meltingCnt * abs(now - posX[j + 1]));
            }
        }
    }

    int ret = 0;
    for (int i = 0; i <= basketCnt; i++)
        for (int flag = 0; flag < 2; flag++)
            ret = max(ret, m * basketCnt - dp[i][basketCnt - i][flag]);

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (x < 0)
            negX.push_back(x);
        else
            posX.push_back(x);
    }

    sort(negX.begin(), negX.end(), greater<>());
    sort(posX.begin(), posX.end());

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, getMaxCandy(i));

    cout << ans;
    return 0;
}