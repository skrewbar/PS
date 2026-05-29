#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

int prefOdd[303030], suffTwo[303030];

void solve() {
    string s;
    cin >> s;

    int n = s.size();

    s = '#' + s;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '3') s[i] = '1';
    }

    int fourCnt = 0;

    for (int i = 1; i <= n; i++) fourCnt += (s[i] == '4');

    prefOdd[0] = 0;
    for (int i = 1; i <= n + 1; i++) prefOdd[i] = prefOdd[i - 1] + (s[i] == '1');

    suffTwo[n + 1] = 0;
    for (int i = n; i >= 0; i--) suffTwo[i] = suffTwo[i + 1] + (s[i] == '2');

    int ans = INF;
    for (int i = 0; i <= n; i++)
        ans = min(ans, prefOdd[i] + suffTwo[i + 1]);

    cout << fourCnt + ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
