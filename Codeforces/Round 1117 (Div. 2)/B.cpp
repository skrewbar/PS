#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    int bea;
    cin >> bea;
    bea += n - 1;

    for (int i = 2; i <= n; i++) {
        int a;
        cin >> a;
    }

    int ver;
    cin >> ver;
    ver += m - 1;

    for (int i = 2; i <= m; i++) {
        int b;
        cin >> b;
    }

    cout << (bea >= ver ? 1 : 2) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
