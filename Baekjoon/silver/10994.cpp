#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int len = 4 * (n - 1) + 1;
    vector<vector<bool>> star(len, vector(len, false));

    for (int i = 0; i < n << 1; i += 2) {
        for (int j = i; j < i + len; j++) {
            star[i][j] = star[i + len - 1][j] =            // 가로
                star[j][i] = star[j][i + len - 1] = true;  // 세로
        }
        len -= 4;
    }

    for (auto row : star) {
        for (bool b : row) {
            cout << (b ? "*" : " ");
        }
        cout << '\n';
    }
}