#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    int aSum = 0;
    int bSum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        aSum += a[i];
        bSum += b[i];
    }

    int ans = -1;
    for (int i = 1; i <= n; i++) {
        if ((bSum) - (aSum - a[i]) <= b[i]) {
            ans = i;
            break;
        }
    }

    if (ans == -1) cout << "impossible";
    else cout << ans;

    return 0;
}
