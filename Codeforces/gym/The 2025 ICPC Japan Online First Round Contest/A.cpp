#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;

        if (n == 0) break;

        long long sum = 0;
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                sum += a*b;
            }
        }

        cout << sum << '\n';
    }

    return 0;
}
