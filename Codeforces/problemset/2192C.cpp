#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a[202020];
ll prefMin[202020], suffMax[202020];

void solve() {
    ll n, h, k;
    cin >> n >> h >> k;

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    prefMin[1] = a[1];
    for (int i = 2; i <= n; i++)
        prefMin[i] = min(prefMin[i - 1], a[i]);

    suffMax[n] = a[n];
    for (int i = n - 1; i >= 1; i--)
        suffMax[i] = max(suffMax[i + 1], a[i]);

    ll reload = h / sum;
    ll answer = reload * (n + k);

    if (h % sum == 0) {
        cout << answer - k << '\n';
        return;
    }
    answer += n;

    h %= sum;

    sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i];

        if (h <= sum + max(0LL, suffMax[i + 1] - prefMin[i])) {
            answer += i - n;
            break;
        }
    }

    cout << answer << '\n';
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
