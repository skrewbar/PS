#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;
    s = '#' + s;

    auto toggle = [](char c) { return c == '0' ? '1' : '0'; };

    int ans = 4;
    auto check = [&](int start) {
        for (int i = start; i <= n; i += 2) {
            if (s[i] == '?') continue;

            ans /= 2;
            for (int j = i - 2; j >= 1; j -= 2) {
                if (s[j] == s[j + 2]) {
                    ans = 0;
                    return;
                }
                s[j] = toggle(s[j + 2]);
            }
            for (int j = i + 2; j <= n; j += 2) {
                if (s[j] == s[j - 2]) {
                    ans = 0;
                    return;
                }
                s[j] = toggle(s[j - 2]);
            }
            break;
        }
    };
    check(1), check(2);

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
