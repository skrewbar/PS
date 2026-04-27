#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

int dp[202020][55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S, T;
    cin >> S >> T;
    
    int N = S.size();
    int M = T.size();

    fill(&dp[0][0], &dp[N + 5][M], -1);
    
    if (S[0] == T[0])
        dp[0][0] = 0;
    
    ll answer = 0;
    int last = dp[0][M - 1] + 1;
    answer += -last + 1;

    for (int i = 1; i < N; i++) {
        dp[i][0] = dp[i - 1][0];
        if (S[i] == T[0])
            dp[i][0] = i;

        for (int j = 1; j < M; j++) {
            dp[i][j] = dp[i - 1][j];

            if (S[i] == T[j])
                maximize(dp[i][j], dp[i - 1][j - 1]);
        }

        maximize(last, dp[i][M - 1] + 1);
        answer += i - last + 1;
    }
    
    cout << answer;

    return 0;
}