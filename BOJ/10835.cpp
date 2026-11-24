#include <bits/stdc++.h>
using namespace std;

int lDeck[2002];
int rDeck[2002];
int dp[2002][2002];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = n; i >= 1; i--) {
        cin >> lDeck[i];
    }
    for (int i = n; i >= 1; i--) {
        cin >> rDeck[i];
    }


    for (int i = 1; i <= n+1; i++) {
        for (int j = 1; j <= n+1; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]);

            if (lDeck[i]>rDeck[j]) {
                dp[i][j] = max(dp[i][j], dp[i][j-1]+rDeck[j]);
            }
        }
    }

    cout << dp[n+1][n+1];


    return 0;
}