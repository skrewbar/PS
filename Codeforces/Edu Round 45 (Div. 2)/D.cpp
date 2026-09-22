#include <bits/stdc++.h>
using namespace std;

bool ans[1010][1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    if (2 <= n and n <= 3 and a == 1 and b == 1) {
        cout << "NO";
        return 0;
    }
    if (a > 1 and b > 1) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";

    bool swapped = (a == 1);
    if (swapped) swap(a, b);
    fill(&ans[0][0], &ans[n][n] + 1, swapped);
    for (int i = 1; i <= n; i++) ans[i][i] = false;

    for (int i = 2; i - 1 <= n - a; i++) {
        ans[i - 1][i] = ans[i][i - 1] = not swapped;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }

    return 0;
}
