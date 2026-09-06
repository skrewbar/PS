#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;
    s = '#' + s;
    s += s[1];

    int score[2] = {};
    for (int i = 1; i <= 2 * n; i++) {
        if (s[i] == '1') {
            if (s[i + 1] != '1') score[i & 1]++;
            else score[~i & 1]++;
        }
    }

    cout << score[1] << ' ' << score[0] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
