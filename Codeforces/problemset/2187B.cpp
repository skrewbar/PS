#include <bits/stdc++.h>
using namespace std;

int x, y;

void solve() {
    cin >> x >> y;

    int d = x & y;
    if (d == 0) {
        cout << x << ' ' << y << '\n';
        return;
    }

    int dmsb = 31 - __builtin_clz(d);

    int p = x, q = y;
    for (int i = dmsb; i >= 0; i--) {
        if (d & (1 << i))
            p -= 1 << i;
        else if (~p & (1 << i) and ~q & (1 << i))
            p += 1 << i;
    }

    for (int i = dmsb + 1; i < 31; i++) {
        if (x & (1 << i) or y & (1 << i))
            continue;
        int a = x;
        a &= ~((1U << (i + 1)) - 1);
        a |= 1 << i;
        
        if (abs(x - a) < abs(x - p) + abs(y - q))
            tie(p, q) = pair(a, y);
        
        a = y;
        a &= ~((1U << (i + 1)) - 1);
        a |= 1 << i;
        
        if (abs(y - a) < abs(x - p) + abs(y - q))
            tie(p, q) = pair(x, a);
    }

    cout << p << ' ' << q << '\n';
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