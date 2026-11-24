#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);


vector<complex<double>> fft(vector<complex<double>> x, bool inverse) {
    int n = x.size();

    for (int i = 0; i < n; i++) {
        int rev = 0;
        for (int j = 1, target = i; j < n; j <<= 1, target >>= 1) {
            rev = (rev << 1) + (target & 1);
        }
        if (i < rev) {
            swap(x[i], x[rev]);
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        complex<double> root(cos(2 * pi / len), sin(2 * pi / len) * (inverse ? 1 : -1));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1, 0);
            for (int j = 0; j < len >> 1; j++) {
                complex even = x[i | j];
                complex odd = x[i | j | len >> 1] * w;
                x[i | j] = even + odd;
                x[i | j | len >> 1] = even - odd;
                w *= root;
            }
        }
    }

    if (inverse) {
        for (auto &elem : x) elem /= n;
    }

    return x;
}


vector<int> multiply(vector<int> a, vector<int> b) {
    int resultLen = a.size() + b.size();
    int n = 1 << ((int)ceil(log2(resultLen - 1)) + 1);
    a.resize(n);
    b.resize(n);

    auto transformedA = fft(vector<complex<double>>(a.begin(), a.end()), false);
    auto transfromedB = fft(vector<complex<double>>(b.begin(), b.end()), false);

    vector<complex<double>> convolution(n);
    for (int i = 0; i < n; i++) {
        convolution[i] = transformedA[i] * transfromedB[i];
    }
    convolution = fft(convolution, true);

    vector<int> ret(resultLen);
    for (int i = 0; i < resultLen; i++) ret[i] = round(convolution[i].real());
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a, b;
    string strA, strB;
    cin >> strA >> strB;
    reverse(strA.begin(), strA.end());
    reverse(strB.begin(), strB.end());

    a.resize(strA.size());
    b.resize(strB.size());

    for (int i = 0; i < strA.size(); i++) {
        a[i] = strA[i] - '0';
    }
    for (int i = 0; i < strB.size(); i++) {
        b[i] = strB[i] - '0';
    }

    auto c = multiply(a, b);
    for (int i = 1; i < c.size(); i++) {
        if (c[i - 1] >= 10) {
            c[i] += c[i - 1] / 10;
            c[i - 1] %= 10;
        }
    }
    if (c.back() == 0) c.pop_back();
    reverse(c.begin(), c.end());
    for (int digit : c) cout << digit;
}