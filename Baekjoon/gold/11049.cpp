#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> DP;
// DP[i][j] 는 i부터 j까지 곱했을 때 최솟값


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n; cin >> n;
    vector<pair<int, int>> matrixes(n, {0, 0});
    for (int i = 0 ; i < n ; i++) {
        int r, c; cin >> r >> c;
        matrixes[i] = {r, c};
    } 

    DP.resize(n, vector<int>(n, INT_MAX));
    for (int i = 0 ; i < n ; i++) {
        DP[i][i] = 0;
    }

    for (int size = 1 ; size < n ; size++) {
        for (int i = 0 ; i + size < n ; i++) {
            for (int j = i ; j < i + size ; j++) {
                DP[i][i+size] = min(
                    DP[i][i+size],
                    DP[i][j] + DP[j+1][i+size]
                    + matrixes[i].first * matrixes[j].second * matrixes[i+size].second
                    );
            }
        }
    }
    cout << DP[0][n-1];


    return 0;
}