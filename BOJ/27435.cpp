#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
using Matrix = vector<vector<T>>;

constexpr ll MOD = 998244353;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<ll> n(t);
    for (int c = 0; c < t; c++) {
        cin >> n[c];
        n[c]--;
    }

    vector<Matrix<ll>> ans(t, {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    });

    Matrix<ll> base = {
        {0, 1, 1},
        {1, 0, 0},
        {0, 1, 0},
    };

    ll exp = 1e18;

    while (exp) {
        for (int c = 0; c < t; c++) {
            if (n[c] & 1) {
                Matrix<ll> res(3, vector<ll>(3));
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        for (int k = 0; k < 3; k++) {
                            res[i][j] += ans[c][i][k] * base[k][j] % MOD;
                            res[i][j] %= MOD;
                        }
                    }
                }
                ans[c] = res;
            }
            n[c] >>= 1;
        }

        Matrix<ll> res(3, vector<ll>(3));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    res[i][j] += base[i][k] * base[k][j] % MOD;
                    res[i][j] %= MOD;
                }
            }
        }
        base = res;
        exp >>= 1;
    }

    for (int c = 0; c < t; c++) {
        cout << accumulate(ans[c][2].begin(), ans[c][2].end(), 0LL) % MOD << '\n';
    }
    return 0;
}