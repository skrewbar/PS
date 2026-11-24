#include <bits/stdc++.h>
using namespace std;

template <typename T>
using Matrix = vector<vector<T>>;

constexpr int MOD = 1000;


Matrix<int> mul(Matrix<int> m1, Matrix<int> m2) {
    Matrix<int> res(m1.size(), vector<int>(m2[0].size()));
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[0].size(); j++) {
            for (int k = 0; k < m1[0].size(); k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
            res[i][j] %= MOD;
        }
    }

    return res;
}


Matrix<int> pow(Matrix<int> base, long long exp) {
    if (exp == 0) {
        Matrix<int> identity(base.size(), vector<int>(base.size(), 0));
        for (int i = 0; i < base.size(); i++) {
            identity[i][i] = 1;
        }
        return identity;
    }

    Matrix<int> temp = pow(base, exp / 2);

    if (exp % 2 == 0) return mul(temp, temp);
    else return mul(mul(temp, temp), base);
}


int main() {
    int n;
    long long b;

    cin >> n >> b;

    Matrix<int> m(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> m[i][j];
    }

    for (vector<int> row : pow(m, b)) {
        for (int e : row) {
            cout << e << ' ';
        }
        cout << '\n';
    }


    return 0;
}