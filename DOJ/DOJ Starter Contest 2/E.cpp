#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int lo = 0, hi = 1e9 + 1;

    for (int i = 0; i < N; i++) {
        int t, c;
        cin >> t >> c;

        if (c == 0) {
            lo = max(lo, t);
        } else {
            hi = min(hi, t - 1);
        }
    }

    if (lo > hi) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    return 0;
}
