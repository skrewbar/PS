#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;


ll pow(ll base, ll exp) {
    if (exp == 0) return 1;

    ll x = pow(base, exp / 2);

    if (exp % 2 == 0) return x * x % MOD;
    else return x * x % MOD * base % MOD;
}


int main() {
    ll a, b;
    cin >> a >> b;

    if (a == 1) cout << b % MOD;
    else cout << (pow(a, b) - 1) * pow(a - 1, MOD-2) % MOD; 

    return 0;
}