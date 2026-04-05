#include <bits/stdc++.h>
using namespace std;

double pi = acos(-1);

void fft(vector<complex<double>>& x, bool inverse) {
    int n = x.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j |= bit;

        if (i < j)
            swap(x[i], x[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        complex<double> unitRoot(cos(2 * pi / len),
                                 sin(2 * pi / len) * (inverse ? 1 : -1));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1, 0);
            for (int j = 0; j < (len >> 1); j++) {
                complex even = x[i | j];
                complex odd = x[i | j | len >> 1] * w;
                x[i | j] = even + odd;
                x[i | j | len >> 1] = even - odd;
                w *= unitRoot;
            }
        }
    }

    if (inverse)
        for (auto& elem : x)
            elem /= n;
}