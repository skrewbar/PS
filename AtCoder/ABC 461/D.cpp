#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int sum[555][555];

int getRangeSum(int r1, int r2, int c1, int c2) {
    return sum[r2][c2] - sum[r2][c1 - 1] - sum[r1 - 1][c2] +
           sum[r1 - 1][c1 - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, K;
    cin >> H >> W >> K;

    ll answer = 0;

    for (int i = 1; i <= H; i++) {
        string S;
        cin >> S;
        S = '#' + S;

        for (int j = 1; j <= W; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] +
                        (S[j] == '1');
        }
    }

    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            for (int s = 1; s <= j; s++) {
                int k = j - s + 1;

                // find lower bound of height
                int lo = 1, hi = i + 1;
                while (lo < hi) {
                    int m = (lo + hi) / 2;

                    if (getRangeSum(i - m + 1, i, k, j) < K) lo = m + 1;
                    else hi = m;
                }
                int lb = lo;

                // find upper bound of height
                lo = 1, hi = i + 1;
                while (lo < hi ) {
                    int m = (lo + hi) / 2;

                    if (getRangeSum(i - m + 1, i, k, j) <= K) lo = m + 1;
                    else hi = m;
                }
                int ub = lo;

                answer += ub - lb;
            }
        }
    }

    cout << answer;

    return 0;
}
