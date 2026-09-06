#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll MOD = 998244353;

ll power(ll base, ll exp, ll mod) {
    ll ret = 1;

    while (exp) {
        if (exp & 1) ret = ret * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }

    return ret;
}

ll factorial[1010101];
ll inv_fact[1010101];

ll comb(ll n, ll r) {
    if (n < 0) return 1;

    return factorial[n] * inv_fact[n - r] % MOD * inv_fact[r] % MOD;
}

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;
    s = '#' + s;

    int count[2] = {};
    int segment[2] = {};

    for (int i = 1; i <= n; i++) {
        int x = s[i] - '0';
        count[x]++;

        if (s[i] != s[i - 1]) segment[x]++;
    }

    cout << comb(count[0] - 1, segment[0] - 1) *
                comb(count[1] - 1, segment[1] - 1) % MOD
         << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll mx = 1'000'000;

    factorial[0] = 1;
    for (ll i = 1; i <= mx; i++) factorial[i] = factorial[i - 1] * i % MOD;

    inv_fact[mx] = power(factorial[mx], MOD - 2, MOD);
    for (ll i = mx - 1; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
