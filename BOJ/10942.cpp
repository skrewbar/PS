#include <iostream>
#include <vector>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }
    vector<vector<int>> dp(n, vector<int>(n, -1));

    dp[0][0] = 1;
    for (int i = 1 ; i < n ; i++) {
        dp[i][i] = 1;

        if (arr[i-1] == arr[i]) dp[i-1][i] = 1;
    }

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j + i < n ; j++) {
            if (arr[j] == arr[j+i] and dp[j+1][j+i-1]) dp[j][j+i] = 1;
        }
    }
    
    int m;
    cin >> m;
    while (m--) {
        int i, j;
        cin >> i >> j;
        cout << dp[i-1][j-1] << '\n';
    }

    return 0;
}