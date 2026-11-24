#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ldouble = long double;

const ldouble pi = acos(-1);

void fft(vector<complex<ldouble>>& x, bool inverse) {
    int n = x.size();

    for (int i = 0; i < n; i++) {
        int rev = 0;

        for (int j = 1, target = i; j < n; j <<= 1, target >>= 1)
            rev = (rev << 1) + (target & 1);

        if (i < rev)
            swap(x[i], x[rev]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        complex<ldouble> root(cos(2 * pi / len),
                              sin(2 * pi / len) * (inverse ? 1 : -1));
        for (int i = 0; i < n; i += len) {
            complex<ldouble> w(1, 0);
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
        for (auto& elem : x)
            elem /= n;
    }
}

vector<int> convolution(vector<int>& A, vector<int>& B) {
    int resultLen = A.size() + B.size();
    int n = 1 << ((int)ceil(log2(resultLen - 1)) + 1);
    A.resize(n);
    B.resize(n);

    vector<complex<ldouble>> transformedA(A.begin(), A.end()),
        transformedB(B.begin(), B.end());

    fft(transformedA, false);
    fft(transformedB, false);

    vector<complex<ldouble>> convolution(n);
    for (int i = 0; i < n; i++)
        convolution[i] = transformedA[i] * transformedB[i];

    fft(convolution, true);

    vector<int> ret(resultLen);
    for (int i = 0; i < resultLen; i++)
        ret[i] = round(convolution[i].real());

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N << 1), B(N << 1);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i + N] = A[i];
    }
    for (int i = N - 1; i >= 0; i--)
        cin >> B[i];

    vector<int> convol = convolution(A, B);
    cout << *max_element(convol.begin(), convol.end());
    return 0;
}