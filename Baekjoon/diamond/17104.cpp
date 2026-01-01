#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

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
        complex unitRoot(cos(2 * pi / len),
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

    if (inverse) {
        for (int i = 0; i < n; i++)
            x[i] /= n;
    }
}

vector<ll> getConvolution(vector<complex<double>> A,
                          vector<complex<double>> B) {
    size_t resLen = 1 << (int)ceil(log2(A.size() + B.size() - 1));

    A.resize(resLen);
    B.resize(resLen);

    fft(A, false);
    fft(B, false);

    vector<complex<double>> con(resLen);
    for (int i = 0; i < resLen; i++)
        con[i] = A[i] * B[i];
    fft(con, true);

    vector<ll> ret(resLen);
    for (int i = 0; i < resLen; i++)
        ret[i] = (ll)round(con[i].real());

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> isPrime(1'000'001, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i < isPrime.size(); i++) {
        if (not isPrime[i])
            continue;

        for (int j = i + i; j < isPrime.size(); j += i)
            isPrime[j] = 0;
    }

    vector<complex<double>> temp(isPrime.begin(), isPrime.end());
    vector<ll> ans = getConvolution(temp, temp);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        println("{}", ans[N] / 2 + isPrime[N / 2]);
    }

    return 0;
}