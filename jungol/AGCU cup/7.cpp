#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    ll sum = 0;
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;

        sum += a;
    }

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            ll l, r, c;
            cin >> l >> r >> c;

            sum += (r - l + 1) * c;
        } else {
            cout << sum << '\n';
        }
    }

    return 0;
}