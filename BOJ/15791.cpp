#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;


ll pow(ll x, ll n) {
    if (n == 0) return 1;

    ll p = pow(x, n / 2) % MOD;

    if (n % 2 == 0) {
        return (p*p) % MOD;
    } else {
        return (p*p) % MOD * (x % MOD);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    if (m >= n/2) m = n - m;

    ll up = 1;
    for (int i = n; i > n-m; i--) {
        up *= i;
        up %= MOD;
    }

    ll down = 1;
    for (int i = m; i > 1; i--) {
        down *= i;
        down %= MOD;
    }

    cout << up * (pow(down, MOD-2) % MOD) % MOD;

    return 0;
}