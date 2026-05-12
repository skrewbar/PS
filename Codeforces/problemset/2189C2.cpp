#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n & 1) {
        cout << n - 1 << ' ';
        for (int i = 2; i <= n - 1; i++)
            cout << (i ^ 1) << ' ';
        cout << 1 << '\n';
    } else {
        int msb = 1 << (31 - __builtin_clz(n));
        int lsb = n & -n;
        if (msb == lsb) {
            cout << -1 << '\n';
            return;
        }

        cout << lsb << ' ';
        for (int i = 2; i <= lsb; i++)
            cout << (i ^ 1) << ' ';
        cout << n << ' ';
        for (int i = lsb + 2; i < n; i++)
            cout << (i ^ 1) << ' ';
        cout << 1 << '\n';
    }
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