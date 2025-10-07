#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int grid[22][22], rowSum[22][22];
bool dp[22][22][40404];
int prevLevel[22][22][40404];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int total = 0;

    // 시계방향으로 90도 회전하여 입력
    for (int j = N; j >= 1; j--) {
        for (int i = 1; i <= N; i++) {
            cin >> grid[i][j];
            total += grid[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            rowSum[i][j] = rowSum[i][j - 1] + grid[i][j];
        }
    }

    dp[0][0][0] = true;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = rowSum[i][j]; k <= total; k++) {
                for (int l = 0; l <= j; l++) {
                    if (dp[i - 1][l][k - rowSum[i][j]]) {
                        dp[i][j][k] = true;
                        prevLevel[i][j][k] = l;
                    }
                }
            }
        }
    }

    int maxLevel = 0;
    int maxHarvest = 0;
    for (int level = 0; level <= N; level++) {
        for (int harvest = 0; harvest <= total; harvest++) {
            if (abs(total - (harvest << 1)) >= abs(total - (maxHarvest << 1)))
                continue;

            if (dp[N][level][harvest]) {
                maxLevel = level;
                maxHarvest = harvest;
            }
        }
    }

    cout << abs(total - (maxHarvest << 1)) << '\n';

    stack<int> ans;
    for (int i = N; i >= 1; i--) {
        ans.push(maxLevel);

        maxLevel = prevLevel[i][maxLevel][maxHarvest];
        maxHarvest -= rowSum[i][ans.top()];
    }

    ASSERT(maxHarvest == 0);

    while (not ans.empty()) {
        cout << ans.top() << ' ';
        ans.pop();
    }

    return 0;
}