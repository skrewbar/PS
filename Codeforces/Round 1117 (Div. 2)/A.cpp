#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    set<char> start;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;

        start.insert(toupper(w.front()));
    }

    bool possible = true;
    for (int i = 0; i < m; i++) {
        string abb;
        cin >> abb;

        for (char c : abb)
            if (not start.contains(c)) possible = false;
        start.insert(abb.front());
    }

    cout << (possible ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
