#include <iostream>
#include <cmath>
using namespace std;
using ll = long long int;

ll gcd(ll a, ll b) {
    ll r = a % b;
    if (r == 0) return b;
    return gcd(b, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll g, l, m, max_divisor = 1;
    cin >> g >> l;
    m = g * l;

    for (ll i = 1 ; i < sqrt(m)+1 ; i++) {
        if ((max_divisor < i) and (m % i == 0) and (gcd(i, m / i) == g)) {
            max_divisor = i;
        }
    }

    cout << max_divisor << ' ' << m / max_divisor;
}