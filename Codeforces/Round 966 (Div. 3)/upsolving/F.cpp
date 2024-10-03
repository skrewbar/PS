#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e9;

struct Rectangle {
    int width, height;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<Rectangle> rects(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> rects[i].width;
            cin >> rects[i].height;
        }
        vector<vector<int>> dp(n+1, vector<int>(k+1, MAX));
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = dp[i-1][j];
                int count = 0, width = rects[i].width, height = rects[i].height;
                for (int a = 1; a <= min(rects[i].width + rects[i].height, j); a++) {
                    if (width <= height) {
                        count += width;
                        height--;
                    } else {
                        count += height;
                        width--;
                    }
                    dp[i][j] = min(dp[i][j], dp[i-1][j-a] + count);
                }
            }
        }
        cout << (dp[n][k] == MAX ? -1 : dp[n][k]) << "\n";
    }
}