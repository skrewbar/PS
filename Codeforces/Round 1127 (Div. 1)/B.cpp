#include <bits/stdc++.h>
using namespace std;

int offset[] = {0, 2, 1};

void solve() {
    int n;
    cin >> n;

    vector<int> ans;

    for (int i = 2 * n; i >= 2; i -= 2) ans.push_back(i);
    for (int i = 2 * n - offset[(1 + ans.size()) % 3]; i >= 2; i -= 2)
        ans.push_back(i);
    for (int i = 2 * n - offset[(2 + ans.size()) % 3]; i >= 2; i -= 2)
        ans.push_back(i);

    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';

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
