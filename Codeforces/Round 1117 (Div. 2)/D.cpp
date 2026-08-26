#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

using ll = long long;

void solve() {
    ll S;
    int q;

    cin >> S >> q;

    vector<ll> factors;
    for (ll i = 1; i <= S / i; i++)
        if (S % i == 0) factors.push_back(i);

    int sz = factors.size();
    for (int i = sz - 1; i >= 0; i--) factors.push_back(S / factors[i]);
    sz = factors.size();

    vector<ll> lenSum(sz);
    lenSum[0] = factors[0];
    for (int i = 1; i < sz; i++)
        lenSum[i] = lenSum[i - 1] + factors[i] - factors[i - 1];

    vector<ll> areaSum(sz);
    areaSum[0] = S / factors[0];
    for (int i = 1; i < sz; i++) {
        areaSum[i] =
            areaSum[i - 1] + (S / factors[i]) * (factors[i] - factors[i - 1]);
    }

    while (q--) {
        ll x, y;
        cin >> x >> y;

        ll ans = areaSum.back();

        if (y <= S / factors[lower_bound(all(lenSum), x) - lenSum.begin()]) {
            cout << x * y << '\n';
            continue;
        }

        auto findIdx = [&](ll coord) {
            int lo = 0, hi = sz;

            while (lo < hi) {
                int mid = (lo + hi) / 2;

                if (S / factors[mid] > coord) lo = mid + 1;
                else hi = mid;
            }

            return lo - 1;
        };

        int i = findIdx(y);
        if (i >= 0) {
            ans -= areaSum[i];
            ans += y * lenSum[i];
        }

        i = findIdx(x);
        if (i >= 0) {
            ans -= areaSum[i];
            ans += x * lenSum[i];
        }

cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
