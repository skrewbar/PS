#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a;
    cin >> a;

    ll p = 2 - (a & 1);
    ll c = (p + a * a / p) / 2;
    ll b = (a * a / p - p) / 2;

    cout << b << ' ' << c;

    return 0;
}