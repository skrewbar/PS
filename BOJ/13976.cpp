#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

constexpr int MOD = 1e9 + 7;

template <typename T>
using Matrix = vector<vector<T>>;

template <typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2) {
    Matrix<T> ret(m1.size(), vector<T>(m2[0].size()));

    for (int i = 0; i < (int)m1.size(); i++) {
        for (int j = 0; j < (int)m2[0].size(); j++) {
            for (int k = 0; k < (int)m2.size(); k++) {
                ret[i][j] +=
                    ((m1[i][k] % MOD) * (m2[k][j] % MOD) % MOD + MOD) % MOD;
                ret[i][j] = (ret[i][j] % MOD + MOD) % MOD;
            }
        }
    }

    return ret;
}

Matrix<ll> base = {
    {3},
    {1},
};
Matrix<ll> mul = {
    {4, -1},
    {1, 0},
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    if (N & 1) {
        print("0");
        return 0;
    }

    N >>= 1;
    N--;
    while (N) {
        if (N & 1)
            base = mul * base;
        mul = mul * mul;
        N >>= 1;
    }

    print("{}", base[0][0]);

    return 0;
}