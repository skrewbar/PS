#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    int INF = K + 1;

    string S, T;
    cin >> S >> T;

    int N = S.size(), M = T.size();

    S = "#" + S;
    T = "#" + T;

    vector<vector<int>> dp(N + 1, vector<int>(2 * K + 1));
    auto dist = [&](int i, int j) -> int & {
        if (abs(i - j) > K) return INF;
        return dp[i][j - i + K];
    };
    for (int i = 1; i <= min(N, K); i++) dist(i, 0) = i;
    for (int j = 1; j <= min(M, K); j++) dist(0, j) = j;

    for (int i = 1; i <= N; i++) {
        for (int j = max(i - K, 1); j <= min(i + K, M); j++) {
            if (S[i] == T[j]) {
                dist(i, j) = dist(i - 1, j - 1);
            } else {
                dist(i, j) = 1 + min({dist(i - 1, j), dist(i, j - 1),
                                      dist(i - 1, j - 1)});
            }
        }
    }

    cout << (dist(N, M) <= K ? "Yes" : "No");

    return 0;
}
