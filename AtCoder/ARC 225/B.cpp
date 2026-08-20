#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N;
    cin >> N;

    bool winExists = false;
    int sz = 0;
    for (int i = 1; i <= N; i++) {
        int A;
        cin >> A;

        if (A == 0) {
            if (sz > 0 and sz != 2) winExists = true;
            sz = 0;
        } else sz++;
    }
    if (sz > 0 and sz != 2) winExists = true;

    cout << (winExists ? "Alice" : "Bob") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
