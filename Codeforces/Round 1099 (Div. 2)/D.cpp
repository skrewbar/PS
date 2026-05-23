#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll INF = 1e15;

ll a[202020], c[202020];

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;
    s = "#" + s;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> c[i];

    if (s[1] == '1' and a[1] != c[1]) {
        cout << "No\n";
        return;
    }
    a[1] = c[1];

    for (int left = 1, right; left <= n; left = right + 1) {
        s[left] = '1';

        right = left;
        while (right + 1 <= n and c[left] == c[right + 1]) right++;

        int first = left;
        while (first <= right and s[first] == '1') first++;

        int last = right;
        while (last >= left and s[last] == '1') last--;

        if (first <= right) a[first] = -INF;

        if (right == n) break;

        if (s[right + 1] == '0') {
            ll sum = c[left];
            for (int i = left + 1; i <= right; i++) sum += a[i];

            a[right + 1] = c[right + 1] - sum;
            continue;
        }

        if (first <= right) {
            ll sum = c[left];
            for (int i = left + 1; i < last; i++) sum += a[i];

            ll afterSum = 0;
            for (int i = last + 1; i <= right + 1; i++) afterSum += a[i];

            a[last] = c[right + 1] - afterSum - sum;
        }
    }

    ll maxSum = -INF;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i];

        maxSum = max(maxSum, sum);
        if (maxSum != c[i]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    for (int k = 1; k <= n; k++) cout << a[k] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
