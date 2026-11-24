#include <bits/stdc++.h>
using namespace std;
using ll = long long;


bool is_prime(ll n) {
    if (n <= 1) return false;

    for (ll i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        while (not is_prime(n)) n++;
        cout << n << '\n';
    }
}