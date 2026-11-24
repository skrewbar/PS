#include <bits/stdc++.h>
using namespace std;

int ans[] = {1, 2, 4, 8, 20};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int X;
        cin >> X;

        if (X <= 4) cout << ans[X];
        else cout << "frogger";
        cout << '\n';
    }

    return 0;
}
