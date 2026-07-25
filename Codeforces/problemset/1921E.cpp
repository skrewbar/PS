#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

void solve() {
    int h, w;
    pair<int, int> a, b;

    cin >> h >> w >> a.x >> a.y >> b.x >> b.y;

    if (a.x >= b.x) {
        cout << "Draw\n";
        return;
    }

    bool swapped = false;
    if (abs(b.x - a.x) % 2 == 0) {
        swapped = true;

        a.x = h - a.x + 1;
        a.y = w - a.y + 1;

        b.x = h - b.x + 1;
        b.y = w - b.y + 1;

        swap(a, b);

        b.x--;
        if (b.y > a.y and b.y < w) b.y++;
        else if (b.y < a.y and b.y > 1) b.y--;
    }

    if (abs(b.y - a.y) <= 1) {
        cout << (swapped ? "Bob" : "Alice") << '\n';
        return;
    }

    int dodge = (b.y > a.y ? w - b.y : b.y - 1);
    a.x += dodge;
    b.x -= dodge;

    if (a.x >= h or b.x <= 1) {
        cout << "Draw\n";
        return;
    }

    if (abs(b.y - a.y) <= (b.x - a.x + 1) / 2) {
        cout << (swapped ? "Bob" : "Alice") << '\n';
        return;
    }

    cout << "Draw\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
