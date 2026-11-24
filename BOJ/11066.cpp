#include <bits/stdc++.h>
using namespace std;

int DP[501][501];
int prefixSum[501];
int file[501];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        fill(&DP[0][0], &DP[500][501], 0);

        for (int i = 1 ; i <= k ; i++) {
            cin >> file[i];
        }
        prefixSum[0] = 0;
        for (int i = 1 ; i <= k ; i++) {
            prefixSum[i] = prefixSum[i-1] + file[i];
        }

        for (int size = 1 ; size < k ; size++) {
            for (int i = 1 ; i + size <= k ; i++) {
                DP[i][i+size] = INT_MAX;
                for (int j = i ; j < i + size ; j++) {
                    DP[i][i+size] = min(
                        DP[i][i+size],
                        DP[i][j] + DP[j+1][i+size] + prefixSum[i+size] - prefixSum[i-1]
                    );
                }
            }
        }
        cout << DP[1][k] << '\n';
    }

    return 0;
}