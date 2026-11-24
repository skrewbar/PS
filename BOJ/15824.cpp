#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll MOD = 1000000007;

ll pw(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
        if (exp & 1) ret = ret * base % MOD;
        exp >>= 1;
        base = base * base % MOD;
    }
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> spicy(n);
    for (int i = 0; i < n; i++) cin >> spicy[i];
    sort(spicy.begin(), spicy.end());

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (pw(2, i) - pw(2, n - i - 1)) * (spicy[i] % MOD) % MOD;
        ans = ((ans % MOD) + MOD) % MOD;
    }
    cout << ans;
}