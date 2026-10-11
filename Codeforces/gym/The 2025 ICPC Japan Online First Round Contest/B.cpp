#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n;
    cin >> n;

    if (n == 0) return false;

    string s;
    cin >> s;

    for (int c = 1; c <= n; c++) {
        string ans;

        for (int i = 0; i < c; i++) ans += s[i];
        ans += s;

        string b = ans.substr(0, n);
        if (s != ans.substr(0, n)) continue;
        cout << ans << '\n';
        break;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (solve());

    return 0;
}
