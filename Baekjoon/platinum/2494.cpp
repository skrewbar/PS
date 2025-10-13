#include <bits/stdc++.h>
#include <climits>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int dp[10101][10], optRotate[10101][10];

int getRightCnt(int from, int to) {
    if (to <= from)
        return from - to;
    return from + 10 - to;
}
int getLeftCnt(int from, int to) {
    if (from <= to)
        return to - from;
    return 10 - from + to;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    fill(&dp[0][0], &dp[N - 1][10], INT_MAX);

    string current, target;
    cin >> current >> target;

    int r = getRightCnt(current[0] - '0', target[0] - '0');
    dp[0][0] = r;
    optRotate[0][0] = -r;
    int l = getLeftCnt(current[0] - '0', target[0] - '0');
    dp[0][l] = getLeftCnt(current[0] - '0', target[0] - '0');
    optRotate[0][l] = l;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            if (dp[i - 1][j] == INT_MAX)
                continue;

            int cur = (current[i] - '0' + j) % 10;

            r = getRightCnt(cur, target[i] - '0');
            if (dp[i - 1][j] + r < dp[i][j]) {
                dp[i][j] = dp[i - 1][j] + r;
                optRotate[i][j] = -r;
            }

            l = getLeftCnt(cur, target[i] - '0');
            int nxtRotate = (j + l) % 10;
            if (dp[i - 1][j] + l < dp[i][nxtRotate]) {
                dp[i][nxtRotate] = dp[i - 1][j] + l;
                optRotate[i][nxtRotate] = l;
            }
        }
    }

    int ans = INT_MAX;
    int lastRoll;
    for (int j = 0; j <= 9; j++) {
        if (dp[N - 1][j] < ans) {
            ans = dp[N - 1][j];
            lastRoll = j;
        }
    }

    cout << ans << '\n';

    stack<int> rotates;
    for (int i = N - 1, j = lastRoll; i >= 0; i--) {
        rotates.push(optRotate[i][j]);
        if (optRotate[i][j] > 0) {
            j -= optRotate[i][j];
            j = (j + 10) % 10;
        }
    }

    for (int i = 1; i <= N; i++) {
        int rotation = rotates.top();
        rotates.pop();

        if (rotation)
            cout << i << ' ' << rotation << '\n';
    }

    return 0;
}