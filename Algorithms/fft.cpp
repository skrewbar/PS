#include <bits/stdc++.h>
using namespace std;

double pi = acos(-1);

vector<complex<double>> fft(vector<complex<double>> x, bool inverse) {
    int n = x.size();

    for (int i = 0; i < n; i++) {
        int rev = 0;
        for (int j = 0; (1 << j) < n; j++)
            rev = (rev << 1) + (i & (1 << j) ? 1 : 0);

        if (i < rev)
            swap(x[i], x[rev]);
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

    return x;
}

int main() {
    // test codes
    vector<int> a = {1, 1, 0, 0}, b = {1, 2, 0, 0};

    vector<complex<double>> aa =
                                fft(vector<complex<double>>(a.begin(), a.end()),
                                    false),
                            bb =
                                fft(vector<complex<double>>(b.begin(), b.end()),
                                    false);

    vector<complex<double>> c(4);
    for (int i = 0; i < 4; i++)
        c[i] = aa[i] * bb[i];

    c = fft(c, true);

    for (int i = 0; i < 4; i++)
        cout << c[i].real() << ' ';

    return 0;
}