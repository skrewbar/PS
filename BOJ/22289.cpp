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

    string strA, strB;
    cin >> strA >> strB;

    vector<int> a((strA.size() + 1) >> 1), b((strB.size() + 1) >> 1);

    for (int i = 0; i < a.size(); i++) {
        int idx = strA.size() - (i << 1) - 1;
        for (int k = 0; k < 2 and idx - k >= 0; k++) {
            a[i] += pow(10, k) * (strA[idx - k] - '0');
        }
    }
    for (int i = 0; i < b.size(); i++) {
        int idx = strB.size() - (i << 1) - 1;
        for (int k = 0; k < 2 and idx - k >= 0; k++) {
            b[i] += pow(10, k) * (strB[idx - k] - '0');
        }
    }

    auto c = multiply(a, b);
    for (int i = 1; i < c.size(); i++) {
        if (c[i - 1] >= 100) {
            c[i] += c[i - 1] / 100;
            c[i - 1] %= 100;
        }
    }
    if (c.back() == 0) c.pop_back();
    cout << c.back();
    for (int i = (int)c.size() - 2; i >= 0; i--) cout << setw(2) << setfill('0') << c[i];
}