#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, m, a, b;
    cin >> n >> m >> a >> b;

    if (gcd(n, a) != 1 or gcd(m, b) != 1) {
        println("NO");
        return;
    }
    
    if (gcd(n, m) >= 3)
        println("NO");
    else
        println("YES");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}