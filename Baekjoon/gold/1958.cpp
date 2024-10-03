#include <bits/stdc++.h>
using namespace std;

int DP[101][101][101];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    string a, b, c;
    cin >> a >> b >> c;
    for (int i = 1 ; i <= a.size() ; i++) {
        for (int j = 1 ; j <= b.size() ; j++) {
            for (int k = 1 ; k <= c.size() ; k++) {
                if (a[i-1] == b[j-1] and b[j-1] == c[k-1]) {
                    DP[i][j][k] = DP[i-1][j-1][k-1] + 1;
                } else {
                    DP[i][j][k] = max({
                        DP[i-1][j][k],
                        DP[i][j-1][k],
                        DP[i][j][k-1]
                    });
                }
            }
        }
    }

    cout << DP[a.size()][b.size()][c.size()];


    return 0;
}