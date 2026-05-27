#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    string X;
    cin >> X;

    if (n & 1 and X[0] == 'b') {
        cout << "NO\n";
        return;
    }

    if (n & 1) {
        for (int i = 1; i < n; i += 2) {
            if (X[i] == '?') continue;

            if (X[i] == X[i + 1]) {
                cout << "NO\n";
                return;
            }
        }
    } else {
        for (int i = 0; i < n; i += 2) {
            if (X[i] == '?') continue;

            if (X[i] == X[i + 1]) {
                cout << "NO\n";
                return;
            }
        }
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
