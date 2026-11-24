#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll d, p, q;
    cin >> d >> p >> q;

    if (p < q)
        swap(p, q);

    ll g = gcd(p, q);
    ll limit = min(d, p * q / g);

    ll answer = d + (-d % p + p) % p;
    for (ll i = 0; i <= limit; i += p) {
        answer = min(answer, d + ((i - d) % q + q) % q);
    }

    cout << answer;
}