#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int ans = 1;

    vector<int> primeFactors;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            ans *= i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1)
        ans *= n;

    for (int factor : primeFactors) ans *= factor;

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
