#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    ll l, r;
    if (n & 1) l = n / 2, r = n / 2 + 1;
    else l = n / 2 - 1, r = n / 2 + 1;

    while (true) {
        if (gcd(n, l) == 1) {
            cout << l;
            return 0;
        } else if (gcd(n, r) == 1) {
            cout << r;
            return 0;
        }
        l--, r++;
    }

    return 0;
}
