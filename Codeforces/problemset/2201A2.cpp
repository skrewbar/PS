#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int a[303030];

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    ll ans = 0;
    ll sum = 0;
    vector<int> stk;
    for (int i = n; i >= 1; i--) {
        while (not stk.empty()) {
            int top = stk.back();
            if (a[top] == a[i] + 1) {
                stk.pop_back();
                sum -= n - top + 1;
            } else
                break;
        }

        stk.push_back(i);
        sum += n - i + 1;

        ans += sum;
    }

    cout << ans << '\n';
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