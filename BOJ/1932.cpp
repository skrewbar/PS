#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> triangle;
    for (int i = 1; i <= n ; i++) {
        vector<int> line(i);
        for (int j = 0 ; j < i ; j++) {
            cin >> line[j];
        }
        triangle.push_back(line);
    }
    
    vector<vector<int>> dp(triangle);
    dp[0][0] = triangle[0][0];
    for (int i = 0 ; i < n-1 ; i++) {
        for (int j = 0 ; j <= i ; j++) {
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + triangle[i+1][j]);
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + triangle[i+1][j+1]);
        }
    }

    int max_sum = 0;
    for (int j = 0 ; j < n ; j++) {
        max_sum = max(max_sum, dp[n-1][j]);
    }
    cout << max_sum;
}