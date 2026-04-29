#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n & 1) {
        cout << n - 1 << ' ';
        for (int i = 2; i <= n - 2; i++)
            cout << (i ^ 1) << ' ';
        cout << 1 << ' ' << n;
    } else {
        cout << n << ' ';
        for (int i = 2; i <= n - 1; i++)
            cout << (i ^ 1) << ' ';
        cout << 1;
    }
    cout << '\n';
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