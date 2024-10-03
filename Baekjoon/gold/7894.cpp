#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t; cin >> t;
    while (t--) {
        int m; cin >> m;
        long double a = 0.0;
        for (int i = 1 ; i <= m ; i++) {
            a += log10l(i);
        }

        cout << (int)floor(a) + 1 << '\n';
    }


    return 0;
}