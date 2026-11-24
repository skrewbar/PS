#include <bits/stdc++.h>
using namespace std;

#define clog2i(x) (32 - __builtin_clz((x) - 1))

using ll = long long;

ll mod1 = 998244353, mod2 = 2281701377;
ll root = 3;

template <typename T>
T power(T base, T exp, T mod) {
    base %= mod;
    T res = 1;

    while (exp) {
        if (exp & 1)
            res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }

    return res;
}

void ntt(vector<ll>& x, ll mod, bool inverse = false) {
    ll r = inverse ? power(root, mod - 2, mod) : root;
    ll n = x.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;

        j |= bit;
        if (i < j)
            swap(x[i], x[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll angle = power(r, (mod - 1) / len, mod);
        ll w = 1;

        for (int i = 0; i < n; i += len) {
            w = 1;
            for (int j = 0; j < (len >> 1); j++) {
                ll even = x[i | j];
                ll odd = x[i | j | len >> 1] * w % mod;
                x[i | j] = (even + odd) % mod;
                x[i | j | len >> 1] = (even - odd + mod) % mod;
                w = w * angle % mod;
            }
        }
    }

    if (inverse) {
        ll inv = power(n, mod - 2, mod);
        for (auto& c : x)
            c = c * inv % mod;
    }
}

void multiply(vector<ll> a, vector<ll> b, vector<ll>& res, ll mod) {
    ntt(a, mod);
    ntt(b, mod);

    for (int i = 0; i < res.size(); i++)
        res[i] = a[i] * b[i] % mod;

    ntt(res, mod, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<ll> f(N + 1);
    for (int i = 0; i <= N; i++)
        cin >> f[i];

    vector<ll> g(M + 1);
    for (int i = 0; i <= M; i++)
        cin >> g[i];

    int sz = 1 << clog2i(N + M + 1);

    f.resize(sz);
    g.resize(sz);

    vector<ll> res1(sz);
    multiply(f, g, res1, mod1);
    vector<ll> res2(sz);
    multiply(f, g, res2, mod2);

    ll ans = 0;
    ll inv1 = power(mod1, mod2 - 2, mod2);
    for (int i = 0; i <= N + M; i++) {
        ll t = (res2[i] - res1[i]) % mod2;
        t = (t + mod2) % mod2;
        t = t * inv1 % mod2;

        ans ^= (res1[i] + mod1 * t) % (mod1 * mod2);
    }

    cout << ans;

    return 0;
}