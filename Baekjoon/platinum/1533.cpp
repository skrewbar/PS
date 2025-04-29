#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1'000'003;

template <typename T>
using Matrix = vector<vector<T>>;

template <typename T>
Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2) {
    Matrix<T> ret(m1.size(), vector<T>(m2[0].size()));

    for (int i = 0; i < m1.size(); i++) {
        for (int j = 0; j < m2[0].size(); j++) {
            for (int k = 0; k < m2.size(); k++) {
                ret[i][j] += m1[i][k] * m2[k][j];
                ret[i][j] %= mod;
            }
        }
    }
    return ret;
}
template <typename T>
Matrix<T> &operator*=(Matrix<T> &m1, const Matrix<T> &m2) {
    return m1 = m1 * m2;
}

template <typename T>
Matrix<T> identityMatrix(ll size) {
    Matrix<T> ret(size, vector<T>(size));
    for (int i = 0; i < size; i++) ret[i][i] = 1;
    return ret;
}

template <typename T>
Matrix<T> pow(Matrix<T> base, ll exp) {
    Matrix<T> ret = identityMatrix<T>(base.size());
    while (exp) {
        if (exp & 1) ret *= base;
        base *= base;
        exp >>= 1;
    }
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, e, t;
    cin >> n >> s >> e >> t;
    s--, e--;

    Matrix<ll> adj(n * 5, vector<ll>(n * 5));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            adj[i * 5 + j + 1][i * 5 + j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            int cost = row[j] - '0';
            if (cost == 0) continue;
            adj[i * 5][j * 5 + cost - 1] = 1;
        }
    }

    cout << pow(adj, t)[s * 5][e * 5];
}