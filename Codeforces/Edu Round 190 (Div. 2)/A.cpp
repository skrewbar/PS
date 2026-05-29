#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;

    ll cost = 0;

    if (3*a > b) {
        cost += n / 3 * b;
        n %= 3;
    } else {
        cost += n * a;
        n = 0;
    }

    cost += min(n * a, b);

    cout << cost << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
