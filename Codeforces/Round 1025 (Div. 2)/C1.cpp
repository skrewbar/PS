#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        int response;

        for (int i = 0; i < 2; i++) {
            cout << "digit" << endl;
            cin >> response;
        }

        for (int i = 8; i >= 1; i >>= 1) {
            cout << "add " << -i << endl;
            cin >> response;
        }

        cout << "add " << n - 1 << endl;
        cin >> response;

        cout << "!" << endl;
        cin >> response;
    }
}