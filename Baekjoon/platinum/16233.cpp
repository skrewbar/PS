#include <bits/stdc++.h>
using namespace std;

int getDigitSum(int n) {
    int ret = 0;

    while (n) {
        ret += n % 10;
        n /= 10;
    }
    
    return ret;
}

void solve() {
    int N;
    cin >> N;

    int X = N;
    while (X % 10)
        X++;

    int ans = -1;
    for (int i = 0; i < 10; i++, X += 10) {
        if (N + getDigitSum(X) == X) {
            ans = X;
            break;
        }
    }
    
    cout << ans << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}