#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp[1000][1001];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, k;
    cin >> n >> k;

    for (int i = 1 ; i < n ; i++) {
        dp[i][0] = 1;
        dp[i][1] = i;
    }

    for (int i = 2 ; i < n ; i++) {
        for (int count = 2 ; count <= k ; count++) {
            dp[i][count] = (dp[i-2][count-1] + dp[i-1][count]) % 1000000003;
        }
    }

    cout << (dp[n-1][k] + dp[n-3][k-1]) % 1000000003;
    

    return 0;
}