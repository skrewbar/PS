#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y, a0, a1, n;
    cin >> x >> y >> a0 >> a1 >> n;

    vector<vector<int>> ans = {
        {a1, 0},
        {0, a0}
    };
    vector<vector<int>> base = {
        {x, y},
        {1, 0}
    };

    while (n) {
        if (n & 1) {
            vector<vector<int>> res(2, vector<int>(2));
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        res[i][j] += base[i][k] * ans[k][j] % 100;
                        res[i][j] %= 100;
                    }
                }
            }
            ans = res;
        }

        vector<vector<int>> res(2, vector<int>(2));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    res[i][j] += base[i][k] * base[k][j] % 100;
                    res[i][j] %= 100;
                }
            }
        }
        base = res;
        n >>= 1;
    }

    cout.width(2);
    cout.fill('0');
    cout << (ans[1][0] + ans[1][1]) % 100;
}