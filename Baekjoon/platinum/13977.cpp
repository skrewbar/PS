#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

const int MOD = 1000000007;
ll factorial[4000001];
ll inverse[4000001];

ll pow(ll x, int n) {
    if (n == 0) return 1;

    ll p = pow(x, n / 2) % MOD;

    if (n % 2 == 0) return p * p % MOD;
    else return p * p % MOD * x % MOD;
}

void init() {
    factorial[0] = 1;
    inverse[0] = 1;
    for (ll i = 1; i < 4000001; i++) {
        factorial[i] = factorial[i-1] * i % MOD;
        inverse[i] = pow(factorial[i], MOD-2) % MOD;
    }
}


int main() {
    fastio();
    init();

    int m;
    cin >> m;
    while (m--) {
        ll n, k;
        cin >> n >> k;

        cout << factorial[n] * inverse[k] % MOD * inverse[n-k] % MOD << '\n';
    }

    return 0;
}