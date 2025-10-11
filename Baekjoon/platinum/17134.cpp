#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

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

    if (inverse)
        for (int i = 0; i < n; i++)
            x[i] /= n;

    return x;
}

vector<ll> multiply(vector<ll> a, vector<ll> b) {
    int resLen = a.size() + b.size() - 1;
    int n = 1 << (int)ceil(log2(resLen));

    a.resize(n);
    b.resize(n);

    auto fa = fft(vector<complex<double>>(a.begin(), a.end()), false);
    auto fb = fft(vector<complex<double>>(b.begin(), b.end()), false);

    vector<complex<double>> convolution(n);
    for (int i = 0; i < n; i++)
        convolution[i] = fa[i] * fb[i];

    convolution = fft(convolution, true);

    vector<ll> ret(resLen);
    for (int i = 0; i < resLen; i++)
        ret[i] = round(convolution[i].real());

    return ret;
}

vector<ll> ans;

void solve() {
    int N;
    cin >> N;
    cout << ans[N] << '\n';
}

constexpr int MAX_N = 1'000'000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> isPrime(MAX_N + 1, 1);
    vector<ll> isEvenSemiPrime(MAX_N + 1, 0);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= MAX_N; i++) {
        if (not isPrime[i])
            continue;
        
        if ((i << 1) <= MAX_N)
            isEvenSemiPrime[i << 1] = true;

        for (int j = i + i; j <= MAX_N; j += i)
            isPrime[j] = 0;
    }

    ans = multiply(isPrime, isEvenSemiPrime);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}