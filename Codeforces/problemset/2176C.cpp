#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()

void solve() {
    int n;
    cin >> n;

    vector<ll> odds, evens;
    for (int i = 1; i <= n; i++) {
        ll a;
        cin >> a;

        if (a & 1)
            odds.push_back(a);
        else
            evens.push_back(a);
    }

    if (odds.empty()) {
        for (int k = 1; k <= n; k++)
            cout << 0 << ' ';
        cout << '\n';
        return;
    }
    ll maxOdd = *max_element(all(odds));
    if (evens.empty()) {
        for (int k = 1; k <= n; k++) {
            if (k & 1)
                cout << maxOdd << ' ';
            else
                cout << 0 << ' ';
        }
        cout << '\n';
        return;
    }

    int oddCnt = odds.size() - 1;
    sort(all(evens));
    ll minEven = evens.front();
    ll sum = maxOdd;

    cout << sum << ' ';
    int k = 2;
    for (int i = evens.size() - 1; i >= 0; i--, k++) {
        sum += evens[i];
        cout << sum << ' ';
    }

    while (k <= n) {
        if (oddCnt >= 2) {
            cout << sum - minEven << ' ';
            cout << sum << ' ';
            oddCnt -= 2;
            k += 2;
        } else {
            cout << 0 << ' ';
            k++;
        }
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