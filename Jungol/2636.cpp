#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll x[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) cin >> x[i];

    auto getCost = [&](ll gap) {
        ll req = 0;
        ll ret = 0;

        for (int i = 0; i < N; i++) {
            ret += abs(x[i] - req);
            req += gap;
        }

        return ret;
    };

    ll l = 1, r = 1e9;
    while (l + 1 < r) {
        ll lm = (l + r) / 2;
        ll rm = lm + 1;

        if (getCost(lm) < getCost(rm)) r = rm - 1;
        else l = lm;
    }

    ll ans = LLONG_MAX;
    for (ll i = l; i <= r; i++) ans = min(ans, getCost(i));

    cout << ans;

    return 0;
}
