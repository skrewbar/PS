#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int p[505050];

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> p[i];

    ll ans = 0;
    ll ldsSum = 0;

    auto calc = [&](int start) {
        ans += ldsSum;

        for (int i = start; i + 2 <= n; i += 2) {
            if (p[i + 1] > p[i + 2]) {
                if (p[i] < p[i + 1]) ldsSum += i + 3;
                else ldsSum += 2 * i + 3;
            } else {
                ldsSum += i + 2;
            }

            ans += ldsSum;
        }
    };

    ldsSum = 1;
    calc(1);

    ldsSum = (p[1] > p[2] ? 3 : 2);
    calc(2);

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
