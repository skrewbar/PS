#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, c;
    cin >> a >> b >> c;

    if (b - a == c - b) {
        cout << "secret " << b - a;
    } else {
        cout << "not secret";
    }

    return 0;
}
