#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr int DRAG = 0, HOLD = 1;

ll cost[202020][2], totalCost[202020][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; i++)
        cin >> cost[i][DRAG];
    for (int i = 1; i <= N; i++)
        cin >> cost[i][HOLD];

    totalCost[1][DRAG] = cost[1][DRAG];
    totalCost[1][HOLD] = cost[1][HOLD];
    for (int i = 2; i <= N; i++) {
        for (int j = DRAG; j <= HOLD; j++) {
            totalCost[i][j] = min(totalCost[i - 1][j] + cost[i][j],
                                  totalCost[i - 1][j ^ 1] + cost[i][j] + K);
        }
    }

    cout << min(totalCost[N][DRAG], totalCost[N][HOLD]);

    return 0;
}