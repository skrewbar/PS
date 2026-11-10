#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const double pi = acos(-1);
void fft(vector<complex<double>> &x, bool inverse = false) {
    int n = x.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;

        j |= bit;
        if (i < j) swap(x[i], x[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * pi / len * (inverse ? -1 : 1);
        complex<double> root(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < (len >> 1); j++) {
                complex even = x[i | j];
                complex odd = x[i | j | len >> 1] * w;
                x[i | j] = even + odd;
                x[i | j | len >> 1] = even - odd;
                w *= root;
            }
        }
    }

    if (inverse)
        for (auto &c : x) c /= n;
}

constexpr string_view RPS = "RPS";
ll winCnt[202020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string s1, s2;
    cin >> s1 >> s2;

    int resSz = 1 << (32 - __builtin_clz((n + m - 1) - 1));

    for (int c = 0; c < 3; c++) {
        vector<complex<double>> v1(resSz), v2(resSz), res(resSz);
        for (int i = 0; i < n; i++) v1[i] = (s1[i] == RPS[(c - 1 + 3) % 3]);
        for (int j = 0; j < m; j++) v2[m - 1 - j] = (s2[j] == RPS[c]);

        fft(v1), fft(v2);
        for (int i = 0; i < resSz; i++) res[i] = v1[i] * v2[i];

        fft(res, true);

        for (int i = 0; i < n + m - 1; i++) winCnt[i] += round(res[i].real());
    }

    ll ans = 0;
    for (int i = m - 1; i < n + m - 1; i++) ans = max(ans, winCnt[i]);
    cout << ans;

    return 0;
}
