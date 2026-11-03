#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string s;
    cin >> s;

    s = s.front() + s + "S";

    int ans = 0;
    for (int i = 1; i <= N + 1; i++) {
        if (s[i] != s[i - 1]) ans++;
    }

    cout << ans;

    return 0;
}