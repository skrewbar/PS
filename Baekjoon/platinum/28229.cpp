#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int LIMIT = 777;

int grid[LIMIT][LIMIT];
int cornerMin[LIMIT], totalMax[LIMIT], innerMax[LIMIT];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }

    int answer = 0;
    for (int u = 1; u <= n; u++) {
        for (int c = 1; c <= m; c++) {
            innerMax[c] = 0;
            totalMax[c] = grid[u][c];
        }

        for (int d = u + 1; d <= n; d++) {
            for (int c = 1; c <= m; c++) {
                totalMax[c] = max(totalMax[c], grid[d][c]);
                cornerMin[c] = min(grid[u][c], grid[d][c]);
            }

            vector<int> left;
            vector<int> rightMax;

            for (int c = 1; c <= m; c++) {
                while (not left.empty() and
                       cornerMin[left.back()] < totalMax[c]) {
                    int minCornerMin =
                        min(cornerMin[c], cornerMin[left.back()]);
                    if (minCornerMin > innerMax[c] and
                        minCornerMin > rightMax.back())
                        answer++;

                    int lastMax = max(rightMax.back(), totalMax[left.back()]);
                    left.pop_back();
                    rightMax.pop_back();
                    if (not rightMax.empty())
                        rightMax.back() = max(rightMax.back(), lastMax);
                }

                if (cornerMin[c] > innerMax[c] and not rightMax.empty() and
                    cornerMin[c] > rightMax.back())
                    answer++;

                if (not rightMax.empty())
                    rightMax.back() = max(rightMax.back(), totalMax[c]);

                if (cornerMin[c] < innerMax[c])
                    continue;

                left.push_back(c);
                rightMax.push_back(innerMax[c]);
            }

            for (int c = 1; c <= m; c++)
                innerMax[c] = max(innerMax[c], grid[d][c]);
        }
    }

    println("{}", answer);

    return 0;
}