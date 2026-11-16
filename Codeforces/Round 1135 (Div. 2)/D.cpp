#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

using ll = long long;

constexpr ll MOD = 1e9 + 7;

ll power(ll base, ll exp) {
    ll ret = 1;

    while (exp) {
        if (exp & 1) ret = ret * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }

    return ret;
}

ll fact[202020];
ll ifact[202020];
ll comb(ll n, ll r) {
    if (n < r) return 0;
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    ll zero = 0;
    vector<ll> pref(n + 1);
    map<ll, vector<int>> poss;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i] - a[n - i + 1];
        if (pref[i] == 0) zero++;

        poss[pref[i]].push_back(i);
    }

    while (q--) {
        int i;
        ll v;
        cin >> i >> v;

        int l = min(i, n - i + 1);
        int r = max(i, n - i + 1) - 1;

        ll w = (i == l ? v : -v);
        ll oldZero = upper_bound(all(poss[0]), r) - lower_bound(all(poss[0]), l);
        ll newZero = upper_bound(all(poss[-w]), r) - lower_bound(all(poss[-w]), l);

        cout << comb(zero - oldZero + newZero - 1, m - 1) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = ifact[0] = 1;
    for (int i = 1; i < 202020; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        ifact[i] = power(fact[i], MOD - 2);
    }

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
